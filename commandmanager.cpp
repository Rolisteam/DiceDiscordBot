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

#include "commandmanager.hpp"
#include "command.hpp"

CommandManager& CommandManager::instance()
{
	static CommandManager mgr;
	return mgr;
}

void CommandManager::insert(Command* command)
{
	if(!command)
		return;
	_commands.insert(command->commandName(), command);
}

CommandManager::~CommandManager()
{
	qDeleteAll(_commands);
}

Command* CommandManager::command(QString name)
{
	if(!_commands.keys().contains(name))
		return nullptr;
	return _commands.value(name);
}

const QMap<QString, Command*>& CommandManager::commands()
{
	return _commands;
}
