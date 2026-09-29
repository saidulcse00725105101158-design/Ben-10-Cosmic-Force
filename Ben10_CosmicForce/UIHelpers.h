// =====================================================================================
// UIHelpers.h
// =====================================================================================
#pragma once
#include <string.h>

bool pointInRect(int px, int py, Rect r) {
	return (px >= r.x && px <= r.x + r.w && py >= r.y && py <= r.y + r.h);
}

void drawButton(Rect r, char *label, double rC, double gC, double bC) {
	iSetColor(rC, gC, bC);
	iFilledRectangle(r.x, r.y, r.w, r.h);
	iSetColor(255, 255, 255);
	iRectangle(r.x, r.y, r.w, r.h);
	iSetColor(255, 255, 255);
	iTextTTF(r.x + r.w / 2 - iTextTTFWidth(label, 18) / 2, r.y + r.h / 2 - 6, label, 18);
}

void iShowImageFlip(int x, int y, int w, int h, unsigned int tex, bool flip) {
	if (flip)
		iShowImage(x + w, y, -w, h, tex);
	else
		iShowImage(x, y, w, h, tex);
}