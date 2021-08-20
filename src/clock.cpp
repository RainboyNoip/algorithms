/*
 *   noiCppUtils, some helpful cpp utils for noi/acm user
 *    Copyright (C) 2020-2021  Rainboy
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "clock.hpp"

noiCppUtils::clock::clock(std::ostream &os):timer(),m_os(os){}

noiCppUtils::clock::~clock(){
    std::istream::fmtflags old_flags = m_os.setf( std::istream::fixed,
            std::istream::floatfield );
    std::streamsize old_prec = m_os.precision( 6 );

    m_os << elapsed() << " s\n"
        << std::endl;
    m_os.flags( old_flags );
    m_os.precision( old_prec );
}
