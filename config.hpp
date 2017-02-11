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

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>

class Config
:public QObject
{
public:
	explicit Config(QObject* parent = 0);
	~Config();
	QJsonObject object();
	void setObject(QJsonObject object);
	void requestFlush();
	void flushNow();
private:
	void flushTimerTimeout();
	void readFile();
	bool _flushNeeded;
	QTimer _flushTimer;
	QJsonObject _object;
};

#endif // CONFIG_HPP
