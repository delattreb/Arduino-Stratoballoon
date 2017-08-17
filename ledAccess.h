//
// Created by Bruno on 17/08/2017.
//

class ledAccess {

private:


public:

	ledAccess() {
	}

	~ledAccess() {
	}
	
	//
	// BlinkLed
	//
	void BlinkLed(int cpt, int time) {
		for (int i = 1; i <= cpt; i++)
		{
			digitalWrite(LED_PIN, HIGH);
			delay(time);
			digitalWrite(LED_PIN, LOW);
			delay(time);
		}
	}
};
