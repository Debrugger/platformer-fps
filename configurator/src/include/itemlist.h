#ifndef __ITEM_LIST_H
#define __ITEM_LIST_H

class Item;

class ItemList;
{
	Item* first_item;
	Item* last_item;

	public:
	ItemList() { first_item = last_item = 0; };
	~ItemList();
	inline Item* FirstItem()	{ return first_item; };
	inline Item* LastItem()		{ return last_item; };
	void SetLastItem(Item* i) 	{ last_item = i; };
	void SetFirstItem(Item*i ) { first_item = i; };
};

#endif //__ITEM_LIST_H
