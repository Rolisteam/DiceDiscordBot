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

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <QDiscord>

class Command
{
public:
	//Require a reference to QDiscord when constructing all commands.
	Command(QDiscord& discord);
	//Virtual destructor. Not having this would be pretty bad.
	virtual ~Command() = default;
	//A dispatch member function that gets called when the command is called by
	//the user.
	virtual void dispatch(QDiscordMessage message, QStringList args) = 0;
	//The command name that will be used to call the command.
	virtual QString commandName() = 0;
	//A description of the command.
	virtual QString helpText() = 0;
	//A list of strings to describe the arguments this command expects.
	//The first element should be the syntax, while the next elements should
	//explain each argument separately.
	virtual QStringList argumentText() = 0;
protected:
	//All commands will get a reference to QDiscord for output.
	QDiscord& _discord;
};

#endif // COMMAND_HPP
