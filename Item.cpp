#include "Item.h"
using namespace UndavItem;

struct UndavItem::Item{
    void* valor;
};

Item* UndavItem::Create(void* item){
    Item* nuevoItem = new Item;
    nuevoItem->valor = item;
    return nuevoItem;
}

void* UndavItem::Get(const Item* item){
    return item->valor;
}

void UndavItem::Destroy(Item* item){
    delete item;
}
