#include "Menu.h"
#include <assert.h>

namespace Arcanoid
{
	void Menu::Init(const MenuItem& item)
	{
		rootItem = item;

		InitMenuItem(rootItem);
		if (rootItem.HasChildrens()) {
			SelectMenuItem(rootItem.GetFrontChild());
		}
	}

	void Menu::InitMenuItem(MenuItem& item)
	{
		for (auto& child : item.GetChildrens())
		{
			child.SetParent(&item);
			InitMenuItem(child);
		}
	}

	void Menu::Draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin)
	{
		MenuItem& expandedItem = GetCurrentContext();

		std::vector<sf::Text*> texts;
		texts.reserve(expandedItem.GetChildrenCount());
		expandedItem.Draw(texts);

		DrawTextList(
			window,
			texts,
			expandedItem.GetChildrenSpacing(),
			expandedItem.GetChildrenOrientation(),
			expandedItem.GetChildrenAlignment(),
			position,
			origin);
	}

	void Menu::PressOnSelectedItem()
	{
		if (!selectedItem) {
			return;
		}

		if (selectedItem->HasCallbackFunction()) {
			selectedItem->PressCallback(*selectedItem);
			return;
		}

		// default behaviour
		if (selectedItem->HasChildrens()) {
			SelectMenuItem(selectedItem->GetFrontChild());
		}
	}

	void Menu::GoBack()
	{
		MenuItem& parent = GetCurrentContext();
		if (&parent != &rootItem) {
			SelectMenuItem(parent);
		}
	}

	void Menu::SwitchToPreviousMenuItem()
	{
		if (!selectedItem) {
			return;
		}

		MenuItem* parent = selectedItem->GetParent();
		assert(parent); // There always should be parent

		auto it = std::find_if(parent->GetChildrens().begin(), parent->GetChildrens().end(), [this](const auto& item) {
			return selectedItem == &item;
			});
		if (it != parent->GetChildrens().begin()) {
			SelectMenuItem(*std::prev(it));
		}
	}

	void Menu::SwitchToNextMenuItem()
	{
		if (!selectedItem) {
			return;
		}

		MenuItem* parent = selectedItem->GetParent();
		assert(parent); // There always should be parent

		auto it = std::find_if(parent->GetChildrens().begin(), parent->GetChildrens().end(), [this](const auto& item) {
			return selectedItem == &item;
			});
		it = std::next(it);
		if (it != parent->GetChildrens().end()) {
			SelectMenuItem(*it);
		}
	}

	void Menu::SelectMenuItem(MenuItem& item)
	{
		assert(&item != &rootItem);

		if (selectedItem == &item)
		{
			return;
		}

		if (!item.IsEnabled())
		{
			// Don't allow to select disabled item
			return;
		}

		if (selectedItem)
		{
			selectedItem->ColorTo(false);
		}

		selectedItem = &item;

		if (selectedItem)
		{
			selectedItem->ColorTo(true);
		}
	}

	MenuItem& Menu::GetCurrentContext()
	{
		return selectedItem ? *(selectedItem->GetParent()) : rootItem;
	}
	bool MenuItem::HasChildrens()
	{	
		return !childrens.empty();
	}
	int MenuItem::GetChildrenCount()
	{
		return (int)childrens.size();
	}
	float MenuItem::GetChildrenSpacing()
	{
		return childrenSpacing;
	}
	Alignment MenuItem::GetChildrenAlignment()
	{
		return childrenAlignment;
	}
	Orientation MenuItem::GetChildrenOrientation()
	{
		return childrenOrientation;
	}
	void MenuItem::Draw(std::vector<sf::Text*>& texts)
	{
		for (auto& child : childrens) {
			if (child.isEnabled) {
				texts.push_back(&child.text);
			}
		}
	}
	std::vector<MenuItem>& MenuItem::GetChildrens()
	{
		return childrens;
	}
	MenuItem& MenuItem::GetFrontChild()
	{
		return childrens.front();
	}
	MenuItem* MenuItem::GetParent()
	{
		return parent;
	}
	void MenuItem::SetParent(MenuItem* ParentPtr)
	{
		parent = ParentPtr;
	}
	void MenuItem::AttachChild(MenuItem& child)
	{
		childrens.push_back(child);
	}
	void MenuItem::PressCallback(MenuItem& item)
	{
		onPressCallback(item);
	}
	bool MenuItem::HasCallbackFunction()
	{
		if (onPressCallback)
			return true;
		else
			return false;
	}
	void MenuItem::ColorTo(bool isSelected)
	{
		sf::Color& color = isSelected ? selectedColor : deselectedColor;
		text.setFillColor(color);
	}
	bool MenuItem::IsEnabled()
	{
		return isEnabled;
	}
	sf::Text* MenuItem::GetHintText()
	{
		return &hintText;
	}
	void MenuItem::SetCallbackFunction(std::function<void(MenuItem& item)> Function)
	{
		onPressCallback = Function;
	}
	void MenuItem::SetTextParameters(bool ForBaseText, std::string String, sf::Font& font, int CharactersSize, sf::Color color)
	{
		sf::Text MenuItem::* ChangedText = ForBaseText ? &MenuItem::text : &MenuItem::hintText;
			
		(this->*ChangedText).setString(String);
		(this->*ChangedText).setFont(font);
		(this->*ChangedText).setCharacterSize(CharactersSize);
		(this->*ChangedText).setFillColor(color);
	}
	void MenuItem::SetPositionParameters(Orientation orientation, Alignment alignment, float spacing)
	{
		childrenOrientation = orientation;
		childrenAlignment = alignment;
		childrenSpacing = spacing;
	}
}
