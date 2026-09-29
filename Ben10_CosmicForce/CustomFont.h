// =====================================================================================
// CustomFont.h
// -------------------------------------------------------------------------------------
// iGraphics only draws text with the built-in GLUT bitmap fonts (see iText() in
// iGraphics.h), which are fixed system fonts and can't be swapped for a custom TTF.
//
// This header adds a second text function, iTextTTF(), that renders with the game's
// own TrueType font instead: font/PlayfulTime-BLBB8.ttf ("Playful Time").
//
// How it works (standard technique for using a real font with legacy/immediate-mode
// OpenGL + GLUT on Windows - no extra font-rasterizing library needed):
//   1) iLoadCustomFont() privately registers the TTF file with Windows (AddFontResourceEx
//      with FR_PRIVATE), so the game can use it by name without installing it system-wide.
//   2) For each point size actually used, we build a Windows GDI HFONT for "Playful Time"
//      at that size and hand it to wglUseFontBitmaps(), which asks GDI to rasterize every
//      glyph and stores each one as an OpenGL display list - one display list per
//      character, exactly like glutBitmapCharacter() does internally for the built-in
//      fonts. iTextTTF() then just calls those display lists with glCallLists(), so it
//      slots in as a drop-in replacement for iText() wherever the game draws text.
//
// Usage:
//   - Call iLoadCustomFont() once, right after iInitialize() (a live GL window/context
//     must exist first) and before the first frame is drawn.
//   - Call iTextTTF(x, y, str, pointSize) anywhere the game used to call iText(...).
//   - Call iTextTTFWidth(str, pointSize) to measure text (used to center button labels).
// =====================================================================================
#pragma once

#include <windows.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "gdi32.lib")

#define CUSTOM_FONT_PATH  "font/PlayfulTime-BLBB8.ttf"   // relative to the .exe, like every other asset
#define CUSTOM_FONT_FACE  "Playful Time"                 // font family name embedded in the TTF itself

#define MAX_TTF_SIZES 8

struct TTFSizeEntry {
	int    pointSize;
	GLuint listBase;   // first of 256 consecutive display lists (one per character 0-255)
	HFONT  hFont;
};

static TTFSizeEntry g_ttfSizes[MAX_TTF_SIZES];
static int          g_ttfSizeCount   = 0;
static bool         g_customFontLoaded = false;

// Registers the TTF with Windows so CreateFont() can find it by family name below.
// Call this once, right after iInitialize().
void iLoadCustomFont() {
	if (AddFontResourceExA(CUSTOM_FONT_PATH, FR_PRIVATE, 0) > 0) {
		g_customFontLoaded = true;
	}
	else {
		g_customFontLoaded = false;
		printf("Warning: could not load custom font \"%s\". Text will fall back to the "
			"default system font matching the name \"%s\".\n", CUSTOM_FONT_PATH, CUSTOM_FONT_FACE);
	}
}

// Unregisters the private font. Not strictly required (Windows cleans this up when the
// process exits), but tidy if you ever want to reload it.
void iUnloadCustomFont() {
	if (g_customFontLoaded) {
		RemoveFontResourceExA(CUSTOM_FONT_PATH, FR_PRIVATE, 0);
		g_customFontLoaded = false;
	}
}

// Finds (building it the first time it's asked for) the set of 256 display lists that
// draw "Playful Time" at the given point size.
static TTFSizeEntry* iGetTTFEntry(int pointSize) {
	for (int i = 0; i < g_ttfSizeCount; i++) {
		if (g_ttfSizes[i].pointSize == pointSize) return &g_ttfSizes[i];
	}

	if (g_ttfSizeCount >= MAX_TTF_SIZES) {
		// Ran out of slots (shouldn't happen - raise MAX_TTF_SIZES if you add more sizes).
		return &g_ttfSizes[0];
	}

	HDC hdc = wglGetCurrentDC();

	HFONT hFont = CreateFontA(
		-pointSize,             // height in pixels (negative = match point size exactly)
		0, 0, 0,
		FW_NORMAL,
		FALSE, FALSE, FALSE,
		DEFAULT_CHARSET,
		OUT_TT_ONLY_PRECIS,     // force TrueType, so we never silently fall back to a bitmap font
		CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE | DEFAULT_PITCH,
		CUSTOM_FONT_FACE);

	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

	GLuint listBase = glGenLists(256);
	wglUseFontBitmaps(hdc, 0, 255, listBase);

	SelectObject(hdc, hOldFont);

	TTFSizeEntry *entry = &g_ttfSizes[g_ttfSizeCount++];
	entry->pointSize = pointSize;
	entry->listBase = listBase;
	entry->hFont = hFont;
	return entry;
}

// Drop-in replacement for iText(x, y, str, <GLUT font>): draws str with the custom TTF.
// pointSize defaults to 18 to match the game's old GLUT_BITMAP_HELVETICA_18 body text.
void iTextTTF(GLdouble x, GLdouble y, char *str, int pointSize = 18) {
	TTFSizeEntry *entry = iGetTTFEntry(pointSize);

	glRasterPos2d(x, y);
	glPushAttrib(GL_LIST_BIT);
	glListBase(entry->listBase);
	glCallLists((GLsizei)strlen(str), GL_UNSIGNED_BYTE, str);
	glPopAttrib();
}

// Measures how wide str would be if drawn with iTextTTF(..., pointSize), in pixels.
// The custom font's glyph widths aren't the same as the old GLUT fonts, so this is used
// (instead of the old strlen()*5 guess) to keep button labels correctly centered.
int iTextTTFWidth(char *str, int pointSize = 18) {
	TTFSizeEntry *entry = iGetTTFEntry(pointSize);

	HDC hdc = wglGetCurrentDC();
	HFONT hOldFont = (HFONT)SelectObject(hdc, entry->hFont);

	SIZE sz = { 0, 0 };
	GetTextExtentPoint32A(hdc, str, (int)strlen(str), &sz);

	SelectObject(hdc, hOldFont);
	return sz.cx;
}
