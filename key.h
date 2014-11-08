/* Despa Diana-Alexandra 311CA */

#ifndef __KEY__H
#define __KEY__H

struct Key {
		std::string s;
		int prio;
		
		/* Supraincarcarea operatorilor de comparatatie, astfel incat elementele
		   din aceasta clasa sa fie ordonate in treap crescator dupa campul prio 
		   si descrescator dupa campul s.*/
		bool operator<(const Key& k)
		{
			if (prio == k.prio)
				return (s > k.s);
			return (prio < k.prio);
		}
		
		bool operator>(const Key& k)
		{
			if (prio == k.prio)
				return (s < k.s);
			return (prio > k.prio);
		}
		
		bool operator==(const Key& k)
		{
			return (s == k.s);
		}
};

#endif
