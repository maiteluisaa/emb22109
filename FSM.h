/*
 * OnCarros.h
 *
 *  Created on: 23 de set de 2022
 *      Author: Aluno
 */

#ifndef FSM_H_
#define FSM_H_

#include <systemc.h>
#include "Counter.h"

enum State {
		Open_p,
		Transition_p,
		Open_c,
		Transition_c
};

SC_MODULE (FSM) {
	sc_in_clk clock;
	sc_in<bool> button;
	sc_out<bool> amarelo_carro;
	sc_out<bool> verde_carro;
	sc_out<bool> vermelho_carro;
	sc_out<bool> verde_pessoa;
	sc_out<bool> vermelho_pessoa;
	sc_in<sc_uint<N> > counter;
	sc_in<State> CurrentState;


	void StateProcess() {

	//State CurrentState;

	switch (CurrentState)
	{
		case 0:
			if(_counter >= 10) // transição após 10s
				CurrentState = Transition_p;
			break;
		case 1:
			if(_counter >= 10) // transição após 10s
				CurrentState = Open_c;
			break;
		case 2:
			if(_counter >= 120 and button == 1) // transição após 10s
				CurrentState = Transition_c;
			break;
		case 3:
			if(_counter >= 10) // transição após 10s
				CurrentState = Open_p;
			break;
		default:
			break;
		}
	}

	void VariableProcess() {

		State CurrentState;

		switch (CurrentState)
		{
			case 0:
				if(_counter >= 10) // transição após 10s
					CurrentState = Transition_p;
				break;
			case 1:
				if(_counter >= 10) // transição após 10s
					CurrentState = Open_c;
				break;
			case 2:
				if(_counter >= 120 and button == 1) // transição após 10s
					CurrentState = Transition_c;
				break;
			case 3:
				if(_counter >= 10) // transição após 10s
					CurrentState = Open_p;
				break;
			default:
				break;
			}
		}

}

SC_CTOR(FSM): _counter("Contador") {

		SC_METHOD(StateProcess);
		sensitive << clock.pos();
		SC_METHOD(VariableProcess);
		sensitive << CurrentState;

		_counter.clock(clock);
		_counter.enable(_enable);
		_counter.reset(_reset);
		_counter.counter_out(_counterout);

	}

private:
	Counter<7> _counter; //  contador até 127 s
	sc_signal<bool> _enable;
	sc_signal<bool> _reset;
	sc_signal<bool> _counterout;

};

#endif /* FSM_H_ */
