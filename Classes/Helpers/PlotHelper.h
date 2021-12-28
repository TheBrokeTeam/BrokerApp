//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#ifndef BROKERAPP_PLOTHELPER_H
#define BROKERAPP_PLOTHELPER_H
#include <implot.h>
#include <implot_internal.h>

class PlotHelper {
public:
    template <typename T>
    static int BinarySearch(const T* arr, int l, int r, T x) {
        if (r >= l) {
            int mid = l + (r - l) / 2;
            if (arr[mid] == x)
                return mid;
            if (arr[mid] > x)
                return BinarySearch(arr, l, mid - 1, x);
            return BinarySearch(arr, mid + 1, r, x);
        }
        return -1;
    }

    static ImPlotTime RoundTimeMinutes(const ImPlotTime& t, long minutesInterval) {
        ImPlotTime t1 = ImPlot::FloorTime(t, ImPlotTimeUnit_Min);
        t1.S -= t1.S  % (minutesInterval*60);

        ImPlotTime t2;
        t2.S = t1.S + minutesInterval*60;
        t2.Us = 0;

        if (t1.S == t2.S)
            return t.Us - t1.Us < t2.Us - t.Us ? t1 : t2;
        return t.S - t1.S < t2.S - t.S ? t1 : t2;
    }

    static void VolumeFormatter(double value, char* buff, int size, void*) {
        static double v[] = {1000000000000,1000000000,1000000,1000,1};
        static const char* p[] = {"T","B","M","k",""};
        if (value == 0) {
            snprintf(buff,size,"0");
            return;
        }
        for (int i = 0; i < 5; ++i) {
            if (fabs(value) >= v[i]) {
                snprintf(buff,size,"%g%s",value/v[i],p[i]);
                return;
            }
        }
        snprintf(buff,size,"%g%s",value/v[4],p[4]);
    }

    template <typename T>
    static inline T RandomRange(T min, T max) {
        T scale = rand() / (T) RAND_MAX;
        return min + scale * ( max - min );
    }


    static ImVec4 RandomColor() {
        ImVec4 col;
        col.x = RandomRange(0.0f,1.0f);
        col.y = RandomRange(0.0f,1.0f);
        col.z = RandomRange(0.0f,1.0f);
        col.w = 1.0f;
        return col;
    }


};

#endif //BROKERAPP_PLOTHELPER_H
