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

#include "interpreter.hpp"
//#include "commands/all.hpp"

Interpreter::Interpreter(QDiscord& discord, QString prefix, QObject* parent)
:QObject(parent), _discord(discord)
{

	connect(_discord.state(), &QDiscordStateComponent::messageCreated,
			this, &Interpreter::messageReceived);
	//Cache the config object so we don't have to keep copying it every time we
	//need it, not that anyone's going to notice the speed difference with a
	//small config file.
	QJsonObject configObject = _config.object();
	if(!configObject.contains("interpreter"))
	{
        configObject["interpreter"] = QJsonObject({{"prefix", "!"}});
		_config.setObject(configObject);
	}
	_prefix = configObject["interpreter"].toObject()["prefix"].toString(prefix);
	registerCommands();
}

void Interpreter::messageReceived(QDiscordMessage message)
{
    QString content = message.content();
    if(!content.startsWith(_prefix))
    {
        qDebug() << "do not start with prefix" << _prefix << message.content();
        return;
    }

    // remove prefix
    content = content.remove(0,1);

    QString result = startDiceParsing(content);

    _discord.rest()->sendMessage(result,message.channelId(),false);
}

void Interpreter::registerCommands()
{

}
QString Interpreter::diceToText(ExportedDiceResult& dice,bool highlight,bool homogeneous)
{
    QStringList resultGlobal;
    foreach(int face, dice.keys())
    {
        QStringList result;
        QStringList currentStreak;
        QList<QStringList> allStreakList;
        ListDiceResult diceResult =  dice.value(face);
        bool previousHighlight=false;
        QString previousColor;
        QString patternColor("");
        foreach (HighLightDice tmp, diceResult)
        {
            if(previousColor != tmp.getColor())
            {
                if(!currentStreak.isEmpty())
                {
                    QStringList list;
                    list << patternColor+currentStreak.join(',');
                    allStreakList.append(list);
                    currentStreak.clear();
                }
                patternColor = QStringLiteral("");

            }
            QStringList diceListStr;
            if((previousHighlight)&&(!tmp.isHighlighted()))
            {
                if(!currentStreak.isEmpty())
                {
                    QStringList list;
                    list << patternColor+currentStreak.join(',');
                    allStreakList.append(list);
                    currentStreak.clear();
                }

            }
            else if((!previousHighlight)&&(tmp.isHighlighted()))
            {
                if(!currentStreak.isEmpty())
                {
                    QStringList list;
                    list << currentStreak.join(',');
                    allStreakList.append(list);
                    currentStreak.clear();
                }
            }
            previousHighlight = tmp.isHighlighted();
            previousColor = tmp.getColor();
            for(int i =0; i < tmp.getResult().size(); ++i)
            {
                qint64 dievalue = tmp.getResult()[i];
                diceListStr << QString::number(dievalue);
            }
            if(diceListStr.size()>1)
            {
                QString first = diceListStr.takeFirst();
                first = QString("%1 [%2]").arg(first).arg(diceListStr.join(','));
                diceListStr.clear();
                diceListStr << first;
            }
            currentStreak << diceListStr.join(' ');
        }

        if(previousHighlight)
        {
            QStringList list;
            list <<  patternColor+currentStreak.join(',');
            allStreakList.append(list);
        }
        else
        {
            if(!currentStreak.isEmpty())
            {
                QStringList list;
                list << currentStreak.join(',');
                allStreakList.append(list);
            }
        }
        foreach(QStringList a, allStreakList)
        {
            result << a;
        }
        if(dice.keys().size()>1)
        {
            resultGlobal << QString(" d%2:(%1)").arg(result.join(",")).arg(face);
        }
        else
        {
            resultGlobal << result.join(",");
        }
    }
    return resultGlobal.join("");
}

QString Interpreter::startDiceParsing(QString cmd)
{
    QString result("");
    bool highlight = true;
    if(m_diceParser.parseLine(cmd))
    {
            m_diceParser.Start();
            if(!m_diceParser.getErrorMap().isEmpty())
            {
                result +=  "```markdown\n# Error:\n" + m_diceParser.humanReadableError() + "\n```";
            }
            else
            {

                ExportedDiceResult list;
                bool homogeneous = true;
                m_diceParser.getLastDiceResult(list,homogeneous);
                QString diceText = diceToText(list,highlight,homogeneous);
                QString scalarText;
                QString str;

                if(m_diceParser.hasIntegerResultNotInFirst())
                {
                    scalarText = QString("%1").arg(m_diceParser.getLastIntegerResult());
                }
                else if(!list.isEmpty())
                {
                    scalarText = QString("%1").arg(m_diceParser.getSumOfDiceResult());
                }
                if(highlight)
                {
                    str = QString("```markdown\n# %1\nDetails:[%3 (%2)]\n```").arg(scalarText).arg(diceText).arg(m_diceParser.getDiceCommand());
                }
                else
                {
                    str = QString("```markdown\n#%1, details:[%3 (%2)]\n```").arg(scalarText).arg(diceText).arg(m_diceParser.getDiceCommand());
                }

                if(m_diceParser.hasStringResult())
                {
                    str = m_diceParser.getStringResult();
                }
                result += str + "\n";
            }
    }
    else
    {
        result += "markdown\n#Error:" + m_diceParser.humanReadableError() + "\n```";
    }


    return result;
}
