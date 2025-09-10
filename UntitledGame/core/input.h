#ifndef INPUT_H
#define INPUT_H

class Input
{
public:
	Input() = default;
	virtual ~Input() = default;

	virtual bool exitRequested() = 0;
	virtual void pollInput() = 0;
private:
};

#endif // INPUT_H