#include "plugin.h"
#include "CFileLoader.h"
#include "CSprite2d.h"
#include "CTimer.h"
#include <iomanip>
#include <iostream>
#include "common.h"
using namespace plugin;
class Watch {
public:
	Watch() {
		static RwTexDictionary *watch = nullptr;
		static CSprite2d  ht, mt, bg;
		Events::initRwEvent += [&] {
			//config_file conf(PLUGIN_PATH("recthud.ini"));
			watch = CFileLoader::LoadTexDictionary(GAME_PATH("models\\watch.txd"));
			ht.m_pTexture = RwTexDictionaryFindNamedTexture(watch, "hr");
			mt.m_pTexture = RwTexDictionaryFindNamedTexture(watch, "min");
			bg.m_pTexture = RwTexDictionaryFindNamedTexture(watch, "watch");
			
			Events::drawingEvent += [&] {
				int hr, min, sec;
				hr = patch::GetUInt(10554219, 1);
				min = patch::GetUInt(10554258, 1);
				double h, hrr, mi, minn, p1, p2, p3, p4, p5, p6, p7, p8, size1, size2;
				double q1, q2, q3, q4, q5, q6, q7, q8;
				h = (double)(hr%12);
				hrr = (h * 30 * 3.14) / 180.0;
				minn = (double)(min * 6);
				mi = (minn * 3.14)/ 180.0;
				size1 = 75.0;
				size2 = 175.0;
				//hr needle
				p1 = cosf(hrr+(mi/12.0))*size1 - sinf(hrr+(mi/12.0)) * (size1)+size2;
				p2 = sinf(hrr+(mi/12.0))*size1 + cosf(hrr+(mi/12.0))* (size1)+size2;
				p3 = cosf(hrr+(mi/12.0))*size1 - sinf(hrr+(mi/12.0)) * (-size1) + size2;
				p4 = sinf(hrr+(mi/12.0))*size1 + cosf(hrr+(mi/12.0))* (-size1) + size2;
				p5 = cosf(hrr+(mi/12.0))*(-size1) - sinf(hrr+(mi/12.0)) * size1 + size2;
				p6 = sinf(hrr+(mi/12.0))*(-size1) + cosf(hrr+(mi/12.0))* size1 + size2;
				p7 = cosf(hrr+(mi/12.0))*(-size1) - sinf(hrr+(mi/12.0)) * (-size1) + size2;
				p8 = sinf(hrr+(mi/12.0))*(-size1) + cosf(hrr+(mi/12.0))* (-size1) + size2;
				//min needle
				q1 = cosf(mi)*size1 - sinf(mi) * (size1)+size2;
				q2 = sinf(mi)*size1 + cosf(mi)* (size1)+size2;
				q3 = cosf(mi)*size1 - sinf(mi) * (-size1) + size2;
				q4 = sinf(mi)*size1 + cosf(mi)* (-size1) + size2;
				q5 = cosf(mi)*(-size1) - sinf(mi) * size1 + size2;
				q6 = sinf(mi)*(-size1) + cosf(mi)* size1 + size2;
				q7 = cosf(mi)*(-size1) - sinf(mi) * (-size1) + size2;
				q8 = sinf(mi)*(-size1) + cosf(mi)* (-size1) + size2;
				//drawing part
				config_file conf(PLUGIN_PATH("watch.ini"));
				double wl, wr, wt, wb;
				int	hl, hb, ml, mb;
				wl = conf["WatchScaleLeft"].asFloat(304.0f);
				wr = conf["WatchScaleRight"].asFloat(86.0f);
				wt = conf["WatchScaleTop"].asFloat(430.0f);
				wb = conf["WatchScaleBottom"].asFloat(20.0f);
				hl = conf["HrNeedleUpDown"].asInt(54);
				hb = conf["HrNeedleLeftRight"].asInt(27);
				ml = conf["MinNeedleUpDown"].asInt(54);
				mb = conf["MinNeedleLeftRight"].asInt(27);
				if (conf["AlwaysON"].asInt() == 1)
				{
					bg.Draw(SCREEN_RECT_BOTTOM_RIGHT(wl, wt, wr, wb), CRGBA(255, 255, 255, 255));
					ht.Draw(SCREEN_COORD_RIGHT(p1 + hb), SCREEN_COORD_BOTTOM(p2 + hl), SCREEN_COORD_RIGHT(p3 + hb),
						SCREEN_COORD_BOTTOM(p4 + hl), SCREEN_COORD_RIGHT(p5 + hb), SCREEN_COORD_BOTTOM(p6 + hl),
						SCREEN_COORD_RIGHT(p7 + hb), SCREEN_COORD_BOTTOM(p8 + hl), CRGBA(255, 255, 255, 255));
					mt.Draw(SCREEN_COORD_RIGHT(q1 + mb), SCREEN_COORD_BOTTOM(q2 + ml), SCREEN_COORD_RIGHT(q3 + mb),
						SCREEN_COORD_BOTTOM(q4 + ml), SCREEN_COORD_RIGHT(q5 + mb), SCREEN_COORD_BOTTOM(q6 + ml),
						SCREEN_COORD_RIGHT(q7 + mb), SCREEN_COORD_BOTTOM(q8 + ml), CRGBA(255, 255, 255, 255));
				}
				else if( conf["AlwaysON"].asInt() == 2)
				{
					static int delayTime;
					if (KeyPressed('Q')) {
						delayTime = CTimer::m_snTimeInMilliseconds + 5000;
					}
					if ((CTimer::m_snTimeInMilliseconds < delayTime))
					{
							bg.Draw(SCREEN_RECT_BOTTOM_RIGHT(wl, wt, wr, wb), CRGBA(255, 255, 255, 255));
							ht.Draw(SCREEN_COORD_RIGHT(p1 + hb), SCREEN_COORD_BOTTOM(p2 + hl), SCREEN_COORD_RIGHT(p3 + hb),
								SCREEN_COORD_BOTTOM(p4 + hl), SCREEN_COORD_RIGHT(p5 + hb), SCREEN_COORD_BOTTOM(p6 + hl),
								SCREEN_COORD_RIGHT(p7 + hb), SCREEN_COORD_BOTTOM(p8 + hl), CRGBA(255, 255, 255, 255));
							mt.Draw(SCREEN_COORD_RIGHT(q1 + mb), SCREEN_COORD_BOTTOM(q2 + ml), SCREEN_COORD_RIGHT(q3 + mb),
								SCREEN_COORD_BOTTOM(q4 + ml), SCREEN_COORD_RIGHT(q5 + mb), SCREEN_COORD_BOTTOM(q6 + ml),
								SCREEN_COORD_RIGHT(q7 + mb), SCREEN_COORD_BOTTOM(q8 + ml), CRGBA(255, 255, 255, 255));
					}
					
				}
			};
		};
		Events::shutdownRwEvent += [] {
			RwTexDictionaryDestroy(watch);
			ht.m_pTexture = nullptr;
			mt.m_pTexture = nullptr;
			bg.m_pTexture = nullptr;
		};
	}

}Watch;