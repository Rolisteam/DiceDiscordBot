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

#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP

#include <QMap>
#include <QList>
#include <QString>

class Command;

class CommandManager
{
public:
	CommandManager(CommandManager& other) = delete;
	CommandManager(CommandManager&& other) = delete;
	CommandManager& operator=(CommandManager other) = delete;
	static CommandManager& instance();
	void insert(Command* command);
	Command* command(QString name);
	const QMap<QString, Command*>& commands();
private:
	CommandManager() = default;
	~CommandManager();
	QMap<QString, Command*> _commands;
};

#define REGISTER_COMMAND(COMMAND_CLASS, ...) \
	CommandManager::instance().insert(new COMMAND_CLASS(__VA_ARGS__))

#endif // COMMANDMANAGER_HPP
