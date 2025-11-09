//       $Id: scanner.h 46519 2022-12-04 12:29:04Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/bin/cepheiden/pfc/trunk/pfc/inc/pfc/scanner.h $
// $Revision: 46519 $
//     $Date: 2022-12-04 13:29:04 +0100 (So., 04 Dez 2022) $
//   $Author: p20068 $
//   Creator: Peter Kulczycki
//  Creation: November 14, 2020
// Copyright: (c) 2021 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg.
//            It is distributed under the Boost Software License (see
//            https://www.boost.org/users/license.html).

#pragma once

#undef  PFC_SCANNER_VERSION
#define PFC_SCANNER_VERSION "2.6.2"

#include <cassert>
#include <format>
#include <functional>
#include <iostream>
#include <locale>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <string>
#include <unordered_map>
#include <variant>

using namespace std::string_literals;
using namespace std::string_view_literals;

namespace pfc { namespace scn { namespace details {

template <typename V> void negate (V &) {
}

template <typename T, typename ...R, typename V> void negate (V & v) {
   if (std::holds_alternative <T> (v))
      std::get <T> (v) *= -1;
   else
      negate <R...> (v);
}

struct symbol_kind final {
   enum class tag_t {
      keyword, terminal_class, terminal_symbol, undefined
   };

   friend std::ostream & operator << (std::ostream & lhs, symbol_kind const & rhs) {
      return lhs << std::format ("{{{},{},{}}}", rhs.str, to_string_view (rhs.tag), rhs.num);
   }

   static constexpr std::string_view to_string_view (tag_t const tag) {
      switch (tag) {
         case tag_t::keyword:         return "kw"sv; break;
         case tag_t::terminal_class:  return "tc"sv; break;
         case tag_t::terminal_symbol: return "ts"sv; break;
         case tag_t::undefined:       return "ud"sv; break;
      }

      return "??"sv;
   }

   constexpr bool operator == (symbol_kind const & rhs) const {
      return (tag == rhs.tag) && (num == rhs.num);
   }

   constexpr bool operator != (symbol_kind const & rhs) const {
      return !operator == (rhs);
   }

   char             chr {};
   std::size_t      num {};
   std::string_view str {"undefined"sv};
   tag_t            tag {tag_t::undefined};
};

constexpr symbol_kind sk_keywd  {' ',   0, "keyword"sv,           symbol_kind::tag_t::keyword};
constexpr symbol_kind sk_ident  {' ',   1, "identifier"sv,        symbol_kind::tag_t::terminal_class};
constexpr symbol_kind sk_int    {' ',   2, "integer"sv,           symbol_kind::tag_t::terminal_class};
constexpr symbol_kind sk_real   {' ',   3, "real"sv,              symbol_kind::tag_t::terminal_class};
constexpr symbol_kind sk_str    {' ',   4, "string"sv,            symbol_kind::tag_t::terminal_class};
constexpr symbol_kind sk_assign {'=',   1, "assign"sv,            symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_caret  {'^',   2, "caret"sv,             symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_colon  {':',   3, "colon"sv,             symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_comma  {',',   4, "comma"sv,             symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_div    {'/',   5, "division"sv,          symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_dquote {'"',   6, "double quote"sv,      symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_eof    {'\0',  7, "end of file"sv,       symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_eol    {'\n',  8, "end of line"sv,       symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_lpar   {'(',   9, "left parenthesis"sv,  symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_minus  {'-',  10, "minus"sv,             symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_mult   {'*',  11, "multiply"sv,          symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_period {'.',  12, "period"sv,            symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_plus   {'+',  13, "plus"sv,              symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_rpar   {')',  14, "right parenthesis"sv, symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_semi   {';',  15, "semicolon"sv,         symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_space  {' ',  16, "space"sv,             symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_tab    {'\t', 17, "tabulator"sv,         symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_uscore {'_',  18, "underscore"sv,        symbol_kind::tag_t::terminal_symbol};
constexpr symbol_kind sk_undef  {};

inline symbol_kind to_symbol_kind (char const c) {
   static std::unordered_map <char, symbol_kind> const map {
      {'=', sk_assign}, {'^',  sk_caret }, {':',  sk_colon }, {',', sk_comma}, {'/', sk_div  },
      {'"', sk_dquote}, {'\0', sk_eof   }, {'\n', sk_eol   }, {'(', sk_lpar }, {'-', sk_minus},
      {'*', sk_mult  }, {'.',  sk_period}, {'+',  sk_plus  }, {')', sk_rpar }, {';', sk_semi },
      {' ', sk_space }, {'\t', sk_tab   }, {'_',  sk_uscore}
   };

   if (auto const pos {map.find (c)}; pos != std::end (map))
      return pos->second;

   return sk_undef;
}

inline auto to_string (char const c) {
   return std::string {to_symbol_kind (c).str};
}

template <typename T> constexpr bool is_alpha (T const c, std::locale const & locale = std::locale::classic ()) {
   return std::isalpha (c, locale) || std::char_traits <T>::eq (c, T {sk_uscore.chr});
}

constexpr bool is_digit (auto const c, std::locale const & locale = std::locale::classic ()) {
   return std::isdigit (c, locale);
}

}   // namespace details

struct exception final : std::runtime_error {
   explicit exception (std::string const & m) : std::runtime_error {m} {
   }
};

}   // namespace scn

struct symbol final {
   constexpr symbol () = default;

   template <typename attr_t = int> constexpr symbol (scn::details::symbol_kind kind, attr_t attr = {})
      : m_kind {std::move (kind)}
      , m_attr {std::move (attr)} {
   }

   constexpr bool operator == (symbol const & rhs) const {
      return (m_kind == rhs.m_kind) && (m_attr == rhs.m_attr);
   }

   constexpr bool operator != (symbol const & rhs) const {
      return !operator == (rhs);
   }

   void clear () {
      m_kind = scn::details::sk_eof;
      m_attr = 0;
   }

   template <typename attr_t> constexpr attr_t const & get_attribute () const {
      return std::get <attr_t> (m_attr);
   }

   template <typename attr_t> constexpr bool holds_attribute () const {
      return std::holds_alternative <attr_t> (m_attr);
   }

   constexpr bool is (char const c) const {
      return (m_kind.tag == scn::details::symbol_kind::tag_t::terminal_symbol) && (m_kind.chr == c);
   }

   constexpr bool is_eof () const {
      return (m_kind == scn::details::sk_eof);
   }

   constexpr bool is_identifier () const {
      return (m_kind == scn::details::sk_ident) && holds_attribute <std::string> ();
   }

   constexpr bool is_integer () const {
      return (m_kind == scn::details::sk_int) && holds_attribute <int> ();
   }

   constexpr bool is_keyword () const {
      return (m_kind.tag == scn::details::symbol_kind::tag_t::keyword) && holds_attribute <std::string> ();
   }

   constexpr bool is_keyword (std::size_t const num) const {
      return is_keyword () && (num > 0) && (m_kind.num == num);
   }

   bool is_keyword (std::string const & name) const {
      return !std::empty (name) && (get_keyword () == name);
   }

   constexpr bool is_real () const {
      return (m_kind == scn::details::sk_real) && holds_attribute <double> ();
   }

   constexpr bool is_number () const {
      return is_integer () || is_real ();
   }

   constexpr bool is_string () const {
      return (m_kind == scn::details::sk_str) && holds_attribute <std::string> ();
   }

   constexpr bool is_terminal_class () const {
      return m_kind.tag == scn::details::symbol_kind::tag_t::terminal_class;
   }

   constexpr bool is_terminal_symbol () const {
      return m_kind.tag == scn::details::symbol_kind::tag_t::terminal_symbol;
   }

   std::string get_identifier () const {
      return is_identifier () ? get_attribute <std::string> () : ""s;
   }

   constexpr int get_integer () const {
      return is_integer () ? get_attribute <int> () : 0;
   }

   std::string get_keyword () const {
      return is_keyword () ? get_attribute <std::string> () : ""s;
   }

   constexpr double get_number () const {
      if (is_integer ()) return get_attribute <int> ();
      if (is_real    ()) return get_attribute <double> ();

      return 0.0;
   }

   constexpr double get_real () const {
      return is_real () ? get_attribute <double> () : 0.0;
   }

   std::string get_string () const {
      return is_string () ? get_attribute <std::string> () : ""s;
   }

   std::ostream & write (std::ostream & out) const {
      out << '{' << m_kind;

      if (is_keyword () || is_terminal_class ())
         std::visit ([&out] (auto const & v) { out << std::format (",'{}'", v); }, m_attr);

      return out << '}';
   }

   friend std::ostream & operator << (std::ostream & lhs, symbol const & rhs) {
      return rhs.write (lhs);
   }

   scn::details::symbol_kind               m_kind {scn::details::sk_eof};
   std::variant <int, double, std::string> m_attr {0};
};

inline std::string to_string (symbol const & sym) {
   static std::ostringstream out; out.str (""); out << sym; return out.str ();
}

class scanner final {
   public:
      static char const * version () {
         return PFC_SCANNER_VERSION;
      }

      scanner () {
         set_istream ();
      }

      explicit scanner (std::istream & in, bool const use_stream_exceptions = false) {
         set_istream (in, use_stream_exceptions);
      }

      scanner (std::istream &&) = delete;

      scanner (scanner const &) = delete;
      scanner (scanner &&) = default;

     ~scanner () = default;

      scanner & operator = (scanner const &) = delete;
      scanner & operator = (scanner &&) = default;

      constexpr symbol const & current_symbol () const {
         return m_current_symbol;
      }

      symbol const & next_symbol () {
         read_next_symbol (); return current_symbol ();
      }

      symbol const & next_symbol (char const chr) {
         if (!is (chr))
            throw scn::exception {
               "Expected '"s + scn::details::to_string (chr) + "' but have " + to_string (m_current_symbol) + '.'
            };

         return next_symbol ();
      }

      symbol const & next_symbol (std::string const & name) {
         if (!is_keyword (name))
            throw scn::exception {
               "Expected keyword '"s + name + "' but have " + to_string (m_current_symbol) + '.'
            };

         return next_symbol ();
      }

      template <typename attr_t> constexpr attr_t const & get_attribute () const {
         return m_current_symbol.get_attribute <attr_t> ();
      }

      std::string get_identifier () const {
         return m_current_symbol.get_identifier ();
      }

      constexpr int get_integer () const {
         return m_current_symbol.get_integer ();
      }

      constexpr double get_number () const {
         return m_current_symbol.get_number ();
      }

      constexpr double get_real () const {
         return m_current_symbol.get_real ();
      }

      std::string get_string () const {
         return m_current_symbol.get_string ();
      }

      constexpr bool is (char const c) const {
         return m_current_symbol.is (c);
      }

      constexpr bool is_eof () const {
         return m_current_symbol.is_eof ();
      }

      constexpr bool is_identifier () const {
         return m_current_symbol.is_identifier ();
      }

      constexpr bool is_integer () const {
         return m_current_symbol.is_integer ();
      }

      constexpr bool is_keyword () const {
         return m_current_symbol.is_keyword ();
      }

      constexpr bool is_keyword (std::size_t const num) const {
         return m_current_symbol.is_keyword (num);
      }

      bool is_keyword (std::string const & name) const {
         return m_current_symbol.is_keyword (name);
      }

      constexpr bool is_number () const {
         return m_current_symbol.is_number ();
      }

      constexpr bool is_real () const {
         return m_current_symbol.is_real ();
      }

      constexpr bool is_string () const {
         return m_current_symbol.is_string ();
      }

      constexpr bool has_symbol () const {
         return !is_eof ();
      }

      std::size_t register_keyword (std::string const & name) {
         if (std::empty (name))
            return 0;

         if (auto const f {m_keywords.find (name)}; f != std::end (m_keywords))
            return f->second.m_kind.num;

         auto const sym {make_keyword_symbol (std::size (m_keywords) + 1, name)};

         m_keywords[name] = sym;

         if (is_identifier () && (current_symbol ().get_identifier () == name))
            m_current_symbol = sym;

         return sym.m_kind.num;
      }

      void set_istream () {
         m_p_in = nullptr; read_next_chr (); read_next_symbol ();
      }

      void set_istream (std::istream & in, bool const use_stream_exceptions = false) {
         if (use_stream_exceptions) {
//          in.exceptions (std::ios::badbit /*| std::ios::eofbit*/ | std::ios::failbit);
         }

         m_p_in = &in; read_next_chr (); read_next_symbol ();
      }

      void set_istream (std::istream &&) = delete;

      void signed_numbers (bool const set = true) {
         m_signed_numbers = set;
      }

      std::ostream & write (std::ostream & out) const {
         out << std::format ("{}registered keywords\n", std::empty (m_keywords) ? "no " : "");

         for (auto const & k : m_keywords)
            out << "  " << k.first << ": " << k.second << '\n';

         return out <<
            "current char:   " << scn::details::to_symbol_kind (m_current_chr) << "\n"
            "current symbol: " << m_current_symbol << '\n';
      }

      friend std::ostream & operator << (std::ostream & lhs, scanner const & rhs) {
         return rhs.write (lhs);
      }

   private:
      static symbol make_keyword_symbol (std::size_t const num, std::string const & name) {
         auto kind {scn::details::sk_keywd}; kind.num = num; return {kind, name};
      }

      constexpr bool is_eof_chr () const {
         return m_current_chr == scn::details::sk_eof.chr;
      }

      constexpr bool is_eol_chr () const {
         return m_current_chr == scn::details::sk_eol.chr;
      }

      constexpr bool is_whitespace_chr () const {
         return (m_current_chr == scn::details::sk_space.chr) || (m_current_chr == scn::details::sk_tab.chr) || is_eol_chr ();
      }

      std::size_t keyword_is_registered (std::string const & name) const {
         if (auto const pos {m_keywords.find (name)}; pos != std::end (m_keywords))
            return pos->second.m_kind.num;

         return 0;
      }

      void read_next_chr () {
         m_current_chr = scn::details::sk_eof.chr;

         if (m_p_in && *m_p_in)
            m_p_in->get (m_current_chr);
      }

      void read_next_chr (char const c) {
         if (m_current_chr != c)
            throw scn::exception {"Expected '"s + c + "' but have '" + m_current_chr + "'."};

         read_next_chr ();
      }

      void read_next_symbol () {
         m_current_symbol.clear (); bool scanned {false};

         while (!scanned) {
            if (is_eof_chr ())
               scanned = true;

            else if (is_whitespace_chr ())
               read_next_chr ();

            else if (scn::details::is_alpha (m_current_chr))
               scanned = scan_keyword_or_identifier ();

            else if (m_current_chr == scn::details::sk_dquote.chr)
               scanned = scan_string ();

            else if (scn::details::is_digit (m_current_chr))
               scanned = try_read_number ();

            else if (m_current_chr == scn::details::sk_period.chr)
               scanned = try_read_number ();

            else if (m_current_chr == scn::details::sk_plus.chr)
               scanned = try_read_number ();

            else if (m_current_chr == scn::details::sk_minus.chr)
               scanned = try_read_number ();

            else if (m_current_chr == scn::details::sk_div.chr) {
               read_next_chr (scn::details::sk_div.chr);

                    if (m_current_chr == scn::details::sk_div .chr) scan_comment_single_line (scn::details::sk_div.chr);
               else if (m_current_chr == scn::details::sk_mult.chr) scan_comment_multi_line  (scn::details::sk_div.chr);

               else {
                  m_current_symbol = scn::details::sk_div; scanned = true;
               }

            } else {
               m_current_symbol = scn::details::to_symbol_kind (m_current_chr);

               if ((scanned = m_current_symbol.is_terminal_symbol ()) == false)
                  throw scn::exception {"Unknown character '"s + m_current_chr + "' encountered."};

               read_next_chr ();
            }
         }
      }

      void scan_comment_multi_line (char prev_chr) {
         assert (prev_chr      == scn::details::sk_div .chr);
         assert (m_current_chr == scn::details::sk_mult.chr);

         auto        depth {0};
         std::string text  {prev_chr};

         do {
            text += m_current_chr; auto annihilate {false};

                 if (prev_chr == scn::details::sk_div .chr) { if (m_current_chr == scn::details::sk_mult.chr) { ++depth; annihilate = true; } }
            else if (prev_chr == scn::details::sk_mult.chr) { if (m_current_chr == scn::details::sk_div .chr) { --depth; annihilate = true; } }

            prev_chr = annihilate ? scn::details::sk_eof.chr : m_current_chr; read_next_chr ();
         } while ((depth > 0) && !is_eof_chr ());
      }

      void scan_comment_single_line (char const prev_chr) {
         assert (prev_chr      == scn::details::sk_div.chr);
         assert (m_current_chr == scn::details::sk_div.chr);

         std::string text {prev_chr};

         while (!is_eol_chr () && !is_eof_chr ()) {
            text += m_current_chr; read_next_chr ();
         }
      }

      bool scan_keyword_or_identifier () {
         assert (scn::details::is_alpha (m_current_chr));

         std::string text;

         while (scn::details::is_alpha (m_current_chr) || scn::details::is_digit (m_current_chr)) {
            text += m_current_chr; read_next_chr ();
         }

         if (auto const num {keyword_is_registered (text)}; num > 0) {
            m_current_symbol = {scn::details::sk_keywd, text}; m_current_symbol.m_kind.num = num;
         } else
            m_current_symbol = {scn::details::sk_ident, text};

         return true;
      }

      bool scan_number (bool have_period = false, bool const is_negative = false) {
         assert (scn::details::is_digit (m_current_chr));

         int integer_part {0};

         if (!have_period) {
            while (scn::details::is_digit (m_current_chr)) {
               integer_part = integer_part * 10 + (m_current_chr - '0'); read_next_chr ();
            }

            if (m_current_chr == scn::details::sk_period.chr) {
               have_period = true; read_next_chr (scn::details::sk_period.chr);
            }

            m_current_symbol = {scn::details::sk_int, integer_part};
         }

         if (have_period) {
            int    fractional_part {0};
            double exponent        {1};

            while (scn::details::is_digit (m_current_chr)) {
               fractional_part  = fractional_part * 10 + (m_current_chr - '0');
               exponent        *= 10;

               read_next_chr ();
            }

            m_current_symbol = {scn::details::sk_real, integer_part + fractional_part / exponent};
         }

         if (is_negative)
            scn::details::negate <int, double> (m_current_symbol.m_attr);

         return true;
      }

      bool scan_string () {
         read_next_chr (scn::details::sk_dquote.chr);

         bool        scanned {false};
         std::string text    {};

         while ((m_current_chr != scn::details::sk_dquote.chr) && !is_eol_chr () && !is_eof_chr ()) {
            text += m_current_chr; read_next_chr ();
         }

         if ((scanned = (m_current_chr == scn::details::sk_dquote.chr)) == true) {
            m_current_symbol = {scn::details::sk_str, text}; read_next_chr ();
         } else
            throw scn::exception {
               "Expected terminating quote in string but have '"s + scn::details::to_string (m_current_chr) + "'."
            };

         return scanned;
      }

      bool try_read_number () {
         if (scn::details::is_digit (m_current_chr))
            return scan_number ();

         else if (m_current_chr == scn::details::sk_period.chr)
            return try_read_number_from_period ();

         bool const have_minus {m_current_chr == scn::details::sk_minus.chr};
         bool const have_plus  {m_current_chr == scn::details::sk_plus .chr};

         read_next_chr ();

         if (m_signed_numbers)
            if (scn::details::is_digit (m_current_chr))
               return scan_number (false, have_minus);

            else if (m_current_chr == scn::details::sk_period.chr)
               return try_read_number_from_period (have_minus);

         if (have_minus) m_current_symbol = scn::details::sk_minus; else
         if (have_plus ) m_current_symbol = scn::details::sk_plus;

         return true;
      }

      bool try_read_number_from_period (bool const is_negative = false) {
         read_next_chr (scn::details::sk_period.chr);

         if (scn::details::is_digit (m_current_chr))
            return scan_number (true, is_negative);

         m_current_symbol = scn::details::sk_period; return true;
      }

      char                                     m_current_chr    {scn::details::sk_eof.chr};   //
      symbol                                   m_current_symbol {};                           //
      std::unordered_map <std::string, symbol> m_keywords       {};                           //
      std::istream *                           m_p_in           {nullptr};                    // non owning
      bool                                     m_signed_numbers {false};                      //
};

}   // namespace pfc
