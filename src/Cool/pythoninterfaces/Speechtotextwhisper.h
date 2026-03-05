// Converted from tmp/k/src/pythoninterfaces/speechtotextwhisper.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2021 Jean-Baptiste Mardelle <jb@kdenlive.org>
    SPDX-FileCopyrightText: 2022 Julius Künzel <julius.kuenzel@kde.org>

    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#pragma once

// #include "speechtotext.h"

// #include <QObject>
// #include <QProcess>

class SpeechToTextWhisper : public SpeechToText
{
    Q_OBJECT
public:
    SpeechToTextWhisper(QObject *parent = nullptr);
    QString runSubtitleScript(QString modelDirectory, QString language, QString audio, QString speech);
    QString subtitleScript() override;
    QString speechScript() override;
    void buildWhisperDeps(bool enableSeamless);
    const QString modelFolder(bool mainFolder = true, bool create = false) override;
    const QStringList getInstalledModels() override;
    bool installNewModel(const QString &modelName = QString()) override;
    QMap<QString, QString> speechLanguages() override;
    const QString installMessage() const override;
    bool installRequirements(QString reqFile) override;
};
