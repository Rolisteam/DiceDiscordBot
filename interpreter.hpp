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

#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <QObject>
#include <QDiscord>
#include <QDebug>
#include "commandmanager.hpp"
#include "config.hpp"
#include "utils.hpp"
#include "diceparser.h"

class Interpreter : public QObject
{
	Q_OBJECT
public:
	explicit Interpreter(QDiscord& discord,
                         QString prefix = "!",
						 QObject* parent = 0);

private://functions
	void messageReceived(QDiscordMessage message);
	void registerCommands();
    QString diceToText(ExportedDiceResult &dice, bool highlight, bool homogeneous);
    QString startDiceParsing(QString cmd);

private://members
	QDiscord& _discord;
	Config _config;
	QString _prefix;
    DiceParser m_diceParser;
};

#endif // INTERPRETER_HPP
