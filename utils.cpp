/*
 * QDiscordSelfBot - An example self-bot written using the QDiscord library.
 * Copyright (C) 2017 george99g
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 */

#include "utils.hpp"

QStringList Utils::tokenizeArguments(QString args)
{
	//This is totally not copied from StackOverflow.
	//Totes.
	QStringList matchList;
	enum class ParserState {
		Beginning, Word, Quote, Escape
	} state = ParserState::Beginning;
	QString buffer;
	for(QChar c : args)
	{
		switch(state)
		{
		case ParserState::Beginning:
			if(c == '\"')
				state = ParserState::Quote;
			else if(c != ' ')
			{
				state = ParserState::Word;
				buffer.append(c);
			}
			break;
		case ParserState::Word:
			if(c == ' ')
			{
				state = ParserState::Beginning;
				matchList.append(buffer);
				buffer.clear();
			}
			else if(c == '\\')
				state = ParserState::Escape;
			else
				buffer.append(c);
			break;
		case ParserState::Quote:
			if(c == '\"')
			{
				state = ParserState::Beginning;
				matchList.append(buffer);
				buffer.clear();
			}
			else if(c == '\\')
				state = ParserState::Escape;
			else
				buffer.append(c);
			break;
		case ParserState::Escape:
			if(c == '\"' || c == '\\')
			{
				state = ParserState::Quote;
				buffer.append(c);
			}
			else if(c == 'n')
			{
				state = ParserState::Quote;
				buffer.append('\n');
			}
			else
			{
				state = ParserState::Quote;
				buffer.append('\\');
				buffer.append(c);
			}
		default:;
		}
	}
	if(state != ParserState::Beginning)
	{
		matchList.append(buffer);
		buffer.clear();
	}
	return matchList;
}
