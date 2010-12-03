#pragma once
class KGCOMMON_API Actor
{
public:
	Actor(void);
	virtual ~Actor(void);
	const std::vector<double> &get_pos() const { return pos; }
	void set_pos(double *p) { pos[0] = p[0]; pos[1] = p[1]; pos[2] = p[2]; }
 protected:
	std::vector<double> pos;
};

