#pragma once
#include "util_includes.h"
namespace RoHAPI {
	
	class Text
	{
	public:
		struct Font
		{
			HAPI_TColour fontColour = HAPI_TColour(255, 255, 255);
			int fontSize = 12;
			int fontWeight = 500;
			std::string fontName = "";
			bool antiAliasing = false;
		};

	private:
		std::string content;
		Font textFont;

	public:

		void Content(std::string content_) { content = content_; };
		std::string Content() const { return content; };
		Font GetFont() { return textFont; };
		void SetFont(const Font newFont) { textFont = newFont; };
	};
}
