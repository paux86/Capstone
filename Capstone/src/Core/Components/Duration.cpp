#include "Duration.h"

Duration::Duration()
{
	creationTime = std::chrono::steady_clock::now();
	ttl = -1;
}
