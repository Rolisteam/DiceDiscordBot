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

#include "selfbot.hpp"

//

SelfBot::SelfBot(QObject* parent)
:QObject(parent), _discord(),_interpreter(_discord)
{
	connect(&_discord, &QDiscord::loginSuccess, this, &SelfBot::loginSuccess);
	connect(&_discord, &QDiscord::loginFailed, this, &SelfBot::loginFailed);
	qDebug()<<"Opening token file...";
	QFile tokenFile(QCoreApplication::applicationDirPath()+"/token.txt");
	if(!tokenFile.exists())
	{
		qDebug()<<tokenFile.fileName()<<"does not exist.";
		qFatal("Could not recover from error.");
	}
	if(!tokenFile.open(QFile::ReadOnly))
	{
		qDebug()<<"Could not open"<<tokenFile.fileName();
		qFatal("Could not recover from error.");
	}
	qDebug()<<"Reading token...";
	QString token = tokenFile.readLine().trimmed();
	qDebug()<<"Starting login...";
    _discord.login(token, QDiscordTokenType::Bot);
	qDebug()<<"Closing token file...";
	tokenFile.close();
}

void SelfBot::loginSuccess()
{
	qDebug()<<"Login successful.";
}

void SelfBot::loginFailed()
{
	qDebug()<<"Login failed.";
	qApp->exit(EXIT_FAILURE); //Stop the application with a fail return code.
}
