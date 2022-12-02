#include "Vertex.h"

namespace Azazel
{
    int sizeOfElement(const ElementType& el)
	{
		switch (el)
		{
			case FLOAT:
			case INT:
			case UNSIGNED_INT:
				return 4;
			case BYTE:
			case UNSIGNED_BYTE:
				return 1;
			case SHORT:
			case UNSIGNED_SHORT:
				return 2;
			default:
				return -1;
		}
		return -1;
	}
}