#pragma once

enum RobotMode {
    MANUAL,
    AUTO
};

extern RobotMode currentMode;

void initExtras();

void setMode(RobotMode newMode);

void runAutoModeLoop();

void activateObstacleAlert(bool activate);

void beep(int durationMs);

void miauEffect();