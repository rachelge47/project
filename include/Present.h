#pragma once
#include "StillObject.h"

class Present : public StillObject {
public:
	using StillObject::StillObject;
private:
};

class KillCatPresent : public Present {
public:
	using Present::Present;
};

class MoreLifePresent : public Present {
public:
	using Present::Present;
};

class FreezePresent : public Present {
public:
	using Present::Present;
};

class IncreaseTimePresent : public Present {
public:
	using Present::Present;
};
