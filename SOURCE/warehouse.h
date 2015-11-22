#ifndef WAREHOUSE_H
#define WAREHOUSE_H

class CWarehouseSystem
{
public:
	CWarehouseSystem();
	virtual ~CWarehouseSystem();

	void GCSendWareHouse(int aIndex);
	void gObjSaveWareHouse(int aIndex);
	int gObjGetWareHouseId(int aIndex, int MapNr);


};
#endif