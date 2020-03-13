/*
 * primary_activity.h
 *
 *  Created on: 26. apr. 2016
 *      Author: Anders
 */

#ifndef primary_activity_h
#define primary_activity_h

class primary_activity {
public:
	primary_activity();

public:
	void Initialize();
	void OnTick();
	void Diag();
	void SetX(int nValue) {m_oDisplay_X.Set(nValue, 2);}
    void SetY(int nValue) {m_oDisplay_Y.Set(nValue, 2);}
    void SetZ(int nValue) {m_oDisplay_Z.Set(nValue, 2);}

private:
	bool CheckInputs(int& rCount, bool bButton, bool bIndex) const;

private:
	aeo1::ssi_display m_oDisplay_X;
    aeo1::ssi_display m_oDisplay_Y;
    aeo1::ssi_display m_oDisplay_Z;
    aeo1::ssi_display m_oDisplay_M;
	int m_nCount_X;
    int m_nCount_Y;
    int m_nCount_Z;
};

#endif /* primary_activity_h */
