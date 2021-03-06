#pragma once
#include "html_tag.h"

namespace litehtml
{
	class el_style : public element
	{
		elements_vector		m_children;
	public:
		el_style(litehtml::document* doc);
		virtual ~el_style();

		virtual void			parse_attributes();
		virtual bool			appendChild(litehtml::element* el);
		virtual const tchar_t*	get_tagName() const;
	};
}
