// Converted from tmp/k/src/audiomixer/mixerseparator.h
// Phase-1 mechanical conversion: framework-specific includes are commented for later U++ wiring.

/*
    SPDX-FileCopyrightText: 2025 Kdenlive contributors
    SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#pragma once

// #include <QWidget>

class MixerSeparator : public QWidget
{
    Q_OBJECT
public:
    explicit MixerSeparator(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override;
};
