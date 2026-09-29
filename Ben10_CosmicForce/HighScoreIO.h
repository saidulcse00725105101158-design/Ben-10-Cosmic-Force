// =====================================================================================
// HighScoreIO.h
// =====================================================================================
#pragma once
#include <stdio.h>

void loadHighScores() {
	FILE *fp = fopen("highscores.txt", "r");
	if (fp == NULL) {
		highScores[0] = highScores[1] = highScores[2] = 0;
		return;
	}
	if (fscanf(fp, "%d %d %d", &highScores[0], &highScores[1], &highScores[2]) != 3) {
		highScores[0] = highScores[1] = highScores[2] = 0;
	}
	fclose(fp);
}

void saveHighScores() {
	FILE *fp = fopen("highscores.txt", "w");
	if (fp == NULL) return;
	fprintf(fp, "%d %d %d\n", highScores[0], highScores[1], highScores[2]);
	fclose(fp);
}

void tryInsertHighScore(int s) {
	if (s > highScores[0]) {
		highScores[2] = highScores[1];
		highScores[1] = highScores[0];
		highScores[0] = s;
	}
	else if (s > highScores[1]) {
		highScores[2] = highScores[1];
		highScores[1] = s;
	}
	else if (s > highScores[2]) {
		highScores[2] = s;
	}
	saveHighScores();
}