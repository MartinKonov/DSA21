#include<iostream>
#include"../DSA_HW2_TEST/interface.h"

int main() {

	//Tree ha;
	//Employee uspeshniq("uspeshniq");
	//Employee a("pesho");
	//Employee b("tesho");
	//Employee c("kesho");
	//Employee d("lesho");
	//Employee e("resho");
	//Employee f("gesho");

	//ha.insert(&a, &uspeshniq, &uspeshniq, 1);
	//ha.insert(&b, &a, &uspeshniq, 1);
	//ha.insert(&c, &a, &uspeshniq,1 );
	//ha.insert(&d, &a, &uspeshniq, 1);
	//ha.insert(&e, &c, &uspeshniq, 1);
	//ha.insert(&f, &c, &uspeshniq, 1);

	//

	//
	//
	Tree h;
	Employee uspeshni("uspeshniq");
	Employee gosho("gosho");
	Employee misho("mishio");
	Employee slavi("slavi");
	Employee pesho("pesho");
	Employee dancho("dancho");
	Employee slav1("slav1");
	Employee slav2("slav2");
	Employee alex("alex");
	Employee boris("boris");
	Employee kamen("kamen");
	Employee mecho("mecho");
	Employee qasd("qasd");


	h.insert(&gosho, &uspeshni, &uspeshni, 1);
	h.insert(&misho, &uspeshni, &uspeshni, 1);
	h.insert(&slavi, &uspeshni, &uspeshni,1);
	h.insert(&pesho, &gosho, &uspeshni, 1);
	h.insert(&dancho, &gosho, &uspeshni, 1);
	h.insert(&alex, &pesho, &uspeshni, 1);
	h.insert(&boris, &dancho, &uspeshni, 1);
	h.insert(&kamen, &dancho, &uspeshni, 1);
	h.insert(&slav1, &slavi, &uspeshni, 1);
	h.insert(&slav2, &slavi, &uspeshni, 1);
	h.insert(&mecho, &slav1, &uspeshni, 1);
	h.insert(&qasd, &mecho, &uspeshni, 1);

	Hierarchy hai("Uspeshnia-Gosho\nUspeshnia-Misho\nUspeshnia-Slavi\nGosho-Dancho\nGosho-Pesho");
	Hierarchy we("Uspeshnia-Gosho\nGosho-Misho\nMisho-Slavi\nGosho-Pesho");

	Hierarchy m = hai.join(we);

	std::cout << m.print();
	int a = 5;

}