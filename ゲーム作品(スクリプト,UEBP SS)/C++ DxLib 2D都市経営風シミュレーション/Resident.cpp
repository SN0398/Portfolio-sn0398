#include "Resident.h"

int ResidentList::GetAllResident()
{
	int Result = 0;
	for (int i = 0; i < ResidentList::Dummy; i++)
	{
		Result += Resident[i];
	}
	return Result;
}