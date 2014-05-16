#ifndef TELEGRAM_H
#define TELEGRAM_H

enum CardinalDirection { UP, RIGHT };
class Telegram
{
public:
	Telegram(CardinalDirection direction, int value) 
	{
		Value = value;
		Direction = direction;
	}

	CardinalDirection Direction;
	int Value;
};

#endif // !TELEGRAM_H
