#include "PhotonComparator.h"

int PCCompare(void* expected, void* actual, int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (((byte*)expected)[i] != ((byte*)actual)[i]) {
			return ! PC_SAME;
		}
	}
	return PC_SAME;
}
