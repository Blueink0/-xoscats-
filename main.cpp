#include <iostream>
#include <map>
#include <cmath>
using namespace std;
typedef long long int ll;
const int N = 1e2 + 10;
const int inf = 0x3f3f3f3f;

void sub1() {
    char l, r, x, y, z;
    int yxq, qzf, now, pnt = 0, sel = 0, ser = 0, pl = 0, pr = 6, odr[12] = {0}, t;
    string ins[12], s;
    map<char, int> dic;
    cout << "按\'左进程字母\' \'右进程字母\'格式输入(不区分大小写),一行两值,允许空格间隔" << endl;
    cin >> l >> r;
    l = l >= 'a' && l <= 'z' ? l - 32 : l;
    r = r >= 'a' && r <= 'z' ? r - 32 : r;
    cout << "若" << l << "的优先权高于" << r << ",则输入0,否则输入1(非零值)" << endl;
    cin >> yxq;
    yxq = min(yxq, 1);
    now = yxq;
    cout << "输入共享变量字母(不区分大小写),一行三值,允许空格间隔" << endl;
    cin >> x >> y >> z;
    x = x >= 'a' && x <= 'z' ? x - 32 : x;
    y = y >= 'a' && y <= 'z' ? y - 32 : y;
    z = z >= 'a' && z <= 'z' ? z - 32 : z;
    cout << "依次输入\'" << x << "\' \'" << y << "\' \'" << z << "\'对应初值,一行三值,空格间隔" << endl;
    cin >> t;
    dic[x] = t;
    cin >> t;
    dic[y] = t;
    cin >> t;
    dic[z] = t;
    cout << "输入优先级调度算法标志,非抢占式为0,抢占式为1(非零)" << endl;
    cin >> qzf;
    qzf = min(qzf, 1);
    cout << "按\'" << l << "1~" << l << "6\',\'" << r << "1~" << r << "6\'顺序依次输入表达式,每行一式(PV操作可只输入\'P\'和\'V\'字母)"
         << endl;
    for (auto & in : ins) {
        cin >> in;
        for (char & j : in)
            j = j >= 'a' && j <= 'z' ? j - 32 : j;
    }
    for (pnt = 0; pnt < 12; pnt++) {
        if (!now && pl < 6 || pr >= 12) {
            if (ins[pl][0] == 'V' && ++ser <= 0 && qzf) now = yxq;
            else if (ins[pl][0] == 'P' && --sel < 0) now = 1;
            odr[pnt] = pl++;
        } else {
            if (ins[pr][0] == 'V' && ++sel <= 0 && qzf) now = yxq;
            else if (ins[pr][0] == 'P' && --ser < 0) now = 0;
            odr[pnt] = pr++;
        }
    }
    for (int i = 0; i < 12; i++) {
        if (!i) cout << endl << "Order:\t";
        if (odr[i] < 6) cout << l << odr[i] + 1 << " ";
        else cout << r << odr[i] - 6 + 1 << " ";
    }
    cout << endl << endl << "init:\t";
    printf("%5d %5d %5d\n", dic[x], dic[y], dic[z]);
    for (int i = 0; i < 12; i++) {
        t = odr[i];
        if (ins[t][0] == 'P' || ins[t][0] == 'V') continue;
        else if (ins[t][2] >= '0' && ins[t][2] <= '9') sscanf(ins[t].substr(2).c_str(), "%d", &dic[ins[t][0]]);
        else {
            if (ins[t][3] == '+') dic[ins[t][0]] = dic[ins[t][2]] + dic[ins[t][4]];
            else if (ins[t][3] == '-') dic[ins[t][0]] = dic[ins[t][2]] - dic[ins[t][4]];
        }
        cout << ins[t] << "\t";
        printf("%5d %5d %5d\n", dic[x], dic[y], dic[z]);
    }
    cout << "final:\t";
    printf("%5d %5d %5d", dic[x], dic[y], dic[z]);
}

void sub2() {
    int art[6] = {-1}, svt[6] = {0}, lft[6] = {1}, gnt[30][2] = {0}, prc[6][2] = {0};
    int p, t, s, n, rrq = 4;
    double sumt = 0, sumw = 0;
    cout << "输入q值" << endl;
    cin >> rrq;
    if (rrq <= 0) rrq = 4;
    cout << "依次输入各进程到达时间,一行五值,空格间隔" << endl;
    for (int i = 1; i < 6; i++) cin >> art[i];
    cout << "依次输入各进程服务时间,一行五值,空格间隔" << endl;
    for (int i = 1; i < 6; i++) {
        cin >> svt[i];
        lft[i] = svt[i];
        svt[0] += svt[i];
    }
    for (p = 1, t = s = n = 0; s < svt[0]; n++) {
        while (p <= 5 && s >= art[p]) {
            gnt[t][0] = p;
            gnt[t][1] = min(lft[p], rrq);
            t++;
            p++;
        }
        if (n && lft[gnt[n - 1][0]]) {
            gnt[t][0] = gnt[n - 1][0];
            gnt[t][1] = min(lft[gnt[n - 1][0]], rrq);
            t++;
        }
        if (lft[gnt[n][0]] <= rrq) {
            prc[lft[0]][0] = gnt[n][0];
            prc[lft[0]][1] = n;
            lft[0]++;
        }
        s += min(lft[gnt[n][0]], rrq);
        lft[gnt[n][0]] -= min(lft[gnt[n][0]], rrq);
    }
    for (int i = 1; i < t; i++) gnt[i][1] += gnt[i - 1][1];
    for (int i = 1; i < 6; i++) prc[i][1] = gnt[prc[i][1]][1];
    cout << endl << "Gannt Chart:" << endl << " |";
    for (int i = 0; i < t; i++) cout << "p" << gnt[i][0] << "|";
    cout << endl;
    cout << " 0|";
    for (int i = 0; i < t; i++) printf("%2d|", gnt[i][1]);
    cout << endl;
    cout << endl << "Px| FT | AT | Tr | Ts | Wr " << endl;
    for (int i = 1; i < 6; i++) {
        int tr = prc[i][1] - art[prc[i][0]];
        double wr = 1.0 * tr / svt[prc[i][0]];
        sumt += tr;
        sumw += wr;
        cout << "p" << prc[i][0] << ":";
        printf("%3d |%3d |%3d |%3d | %-5.3f\n", prc[i][1], art[prc[i][0]], tr, svt[prc[i][0]], wr);
    }
    printf("\nT=%.2f\nW=%.2f", sumt / 5, sumw / 5);
}

void sub3() {
    int rsc[3], avl[3], max[5][3], alc[5][3], nid[5][3], prc[5] = {0};
    int vis[5] = {0}, f = 0;
    cout << "输入全部三种资源总量,一行三值,空格间隔" << endl;
    for (int i = 0; i < 3; i++) {
        cin >> rsc[i];
        avl[i] = rsc[i];
    }
    cout << "依次输入进程的max和allocation,一行六值,空格间隔" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) cin >> max[i][j];
        for (int j = 0; j < 3; j++) cin >> alc[i][j];
        for (int j = 0; j < 3; j++) nid[i][j] = max[i][j] - alc[i][j];
        for (int j = 0; j < 3; j++) avl[j] -= alc[i][j];
    }
    cout << endl << "Px|   Max   |Alloca...|   Need  |Available" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "p" << i << ":";
        for (int j = 0; j < 3; j++) printf("%3d", max[i][j]);
        cout << "|";
        for (int j = 0; j < 3; j++) printf("%3d", alc[i][j]);
        cout << "|";
        for (int j = 0; j < 3; j++) printf("%3d", nid[i][j]);
        cout << "|";
        if (!i) for (int j = 0; j < 3; j++) printf("%3d", avl[j]);
        cout << endl;
    }
    cout << endl << "Px|   Work  |   Need  |Alloca...|Work+Allo|Finish" << endl;
    for (int i = 0; f != 5; i++, i %= 5)
        if (!vis[i] && nid[i][0] <= avl[0] && nid[i][1] <= avl[1] && nid[i][2] <= avl[2]) {
            vis[i] = 1;
            prc[f++] = i;
            cout << "p" << i << ":";
            for (int j = 0; j < 3; j++) printf("%3d", avl[j]);
            cout << "|";
            for (int j = 0; j < 3; j++) printf("%3d", nid[i][j]);
            cout << "|";
            for (int j = 0; j < 3; j++) printf("%3d", alc[i][j]);
            cout << "|";
            for (int j = 0; j < 3; j++) {
                avl[j] += alc[i][j];
                printf("%3d", avl[j]);
            }
            cout << "|";
            cout << "true" << endl;
        }
    cout << endl << "safe" << endl << endl << "安全序列:{";
    for (int i = 0; i < 5; i++) {
        cout << "p" << prc[i];
        if (i - 4) cout << ",";
        else cout << "}";
    }
}

void sub4()//Clock
{
    int frm, nfp, ram[5], flg[5], prl[25], rsl[25], mor[5][25], t, a = 0, b = 0;
    for (int i = 0; i < 5; i++) ram[i] = flg[i] = -1;
    for (int i = 0; i < 25; i++) prl[i] = rsl[i] = -1;
    for (int i = 0; i < 5; i++) for (int j = 0; j < 25; j++) mor[i][j] = -1;
    cout << "输入所分配的物理块数(最高为5)" << endl;
    cin >> frm;
    cout << "输入NF指针初始指向,高地址输入1(正值),低地址输入0" << endl;
    cin >> nfp;
    if (nfp) nfp = frm - 1;
    cout << "输入已装入内存中的页面号,空格间隔,最后不要带空格,只有换行" << endl;
    for (int i = 0; cin >> ram[i]; i++) if (getchar() == '\n') break;
    cout << "输入内存中页面对应访问位,空格间隔,最后不要带空格,只有换行" << endl;
    for (int i = 0; cin >> flg[i]; i++) if (getchar() == '\n') break;
    cout << "依次输入页面访问串值,空格间隔,最后不要带空格,只有换行" << endl;
    for (int i = 0; cin >> rsl[i]; i++) if (getchar() == '\n') break;
    for (int i = 0; rsl[i] >= 0 && i < 25; i++) {
        int j;
        for (j = 0; j < frm; j++)
            if (ram[j] == rsl[i]) {
                flg[j] = 1;
                j = -1;
                break;
            }
        if (j < 0) continue;
        while (1) {
            if (flg[nfp] > 0) {
                flg[nfp] = 0;
                nfp++;
                nfp %= frm;
            } else {
                a++;
                prl[i] = ram[nfp];
                ram[nfp] = rsl[i];
                flg[nfp] = 1;
                for (j = 0; j < frm; j++) mor[j][i] = ram[j];
                nfp++;
                nfp %= frm;
                break;
            }
        }
    }
    cout << endl << endl << " PR:|";
    for (int i = 0; rsl[i] >= 0 && i < 25; i++) {
        if (prl[i] >= 0) {
            cout << prl[i] << "|";
            b++;
        }
        else cout << " |";
    }
    cout << endl << endl << " RS:|";
    for (int i = 0; rsl[i] >= 0 && i < 25; i++) cout << rsl[i] << "|";
    cout << endl << endl << "RAM:|";
    for (int j = 0; j < frm; j++) {
        if (j) cout << "    |";
        for (int i = 0; rsl[i] >= 0 && i < 25; i++) {
            if (mor[j][i] >= 0) cout << mor[j][i] << "|";
            else cout << " |";
        }
        cout << endl;
    }
    cout << endl << " PF =" << a << endl;
    cout << endl << " PR =" << b << endl;
    cout << endl << "Pages to be replaced" << endl << "list:";
    t = b;
    for (int i = 0; rsl[i] >= 0 && i < 25; i++)
        if (prl[i] >= 0) {
            if (t - b) cout << ",";
            t--;
            cout << prl[i];
        }
    cout << endl << endl << "Page P and access bit A" << endl << "list:";
    for (int i = 0; i < frm; i++) {
        if (i) cout << ",";
        cout << ram[i] << "-" << flg[i];
    }
}

void sub4_1()//Optimal
{
    int frm, ram[5], flg[5], prl[25], rsl[25], mor[5][25], t, a = 0, b = 0;
    for (int i = 0; i < 5; i++) ram[i] = flg[i] = -1;
    for (int i = 0; i < 25; i++) prl[i] = rsl[i] = -1;
    for (int i = 0; i < 5; i++) for (int j = 0; j < 25; j++) mor[i][j] = -1;
    cout << "输入所分配的物理块数(最高为5)" << endl;
    cin >> frm;
    cout << "输入已装入内存中的页面号,空格间隔,最后不要带空格,只有换行" << endl;
    for (int i = 0; cin >> ram[i]; i++) if (getchar() == '\n') break;
    cout << "依次输入页面访问串值,空格间隔,最后不要带空格,只有换行" << endl;
    for (int i = 0; cin >> rsl[i]; i++) if (getchar() == '\n') break;
    for (int i = 0; rsl[i] >= 0 && i < 25; i++) {
        int j;
        for (j = 0; j < frm; j++) {
            if (ram[j] == rsl[i]) break;
            else if (ram[j] == -1) {
                a++;
                ram[j] = rsl[i];
                for (t = 0; t < frm; t++) mor[t][i] = ram[t];
                break;
            }
        }
        if (j - frm) continue;
        for (j = 0; j < frm; j++) {
            flg[j] = 25;
            for (t = i + 1; rsl[t] >= 0 && t < 25; t++)
                if (ram[j] == rsl[t]) {
                    flg[j] = t;
                    break;
                }
        }
        for (j = t = 0; j < frm; j++) if (flg[t] < flg[j]) t = j;
        a++;
        b++;
        prl[i] = ram[t];
        ram[t] = rsl[i];
        for (j = 0; j < frm; j++) mor[j][i] = ram[j];
    }
    cout << endl << endl << " PR:|";
    for (int i = 0; rsl[i] >= 0 && i < 25; i++) {
        if (prl[i] >= 0) cout << prl[i] << "|";
        else cout << " |";
    }
    cout << endl << endl << " RS:|";
    for (int i = 0; rsl[i] >= 0 && i < 25; i++) cout << rsl[i] << "|";
    cout << endl << endl << "RAM:|";
    for (int j = 0; j < frm; j++) {
        if (j) cout << "    |";
        for (int i = 0; rsl[i] >= 0 && i < 25; i++) {
            if (mor[j][i] >= 0) cout << mor[j][i] << "|";
            else cout << " |";
        }
        cout << endl;
    }
    cout << endl << " PF =" << a << endl;
    cout << endl << " PR =" << b << endl;
    cout << endl << "Pages to be replaced" << endl << "list:";
    t = b;
    for (int i = 0; rsl[i] >= 0 && i < 25; i++)
        if (prl[i] >= 0) {
            if (t - b) cout << ",";
            t--;
            cout << prl[i];
        }
}

void sub4_2()//LRU
{
    int frm, ram[5], flg[5], prl[25], rsl[25], mor[5][25], t, a = 0, b = 0;
    for (int i = 0; i < 5; i++) ram[i] = flg[i] = -1;
    for (int i = 0; i < 25; i++) prl[i] = rsl[i] = -1;
    for (int i = 0; i < 5; i++) for (int j = 0; j < 25; j++) mor[i][j] = -1;
    cout << "输入所分配的物理块数(最高为5)" << endl;
    cin >> frm;
    cout << "依次输入已装入内存中的页面号,空格间隔,最后不要带空格,只有换行" << endl;
    for (int i = 0; cin >> ram[i]; i++) if (getchar() == '\n') break;
    cout << "依次输入页面访问串值,空格间隔,最后不要带空格,只有换行" << endl;
    for (int i = 0; cin >> rsl[i]; i++) if (getchar() == '\n') break;
    for (int i = 0; rsl[i] >= 0 && i < 25; i++) {
        int j;
        for (j = 0; j < frm; j++) {
            if (ram[j] == rsl[i]) break;
            else if (ram[j] == -1) {
                a++;
                ram[j] = rsl[i];
                for (t = 0; t < frm; t++) mor[t][i] = ram[t];
                break;
            }
        }
        if (j - frm) continue;
        for (j = 0; j < frm; j++) {
            flg[j] = -1;
            for (t = i - 1; t >= 0 && rsl[t] >= 0; t--)
                if (ram[j] == rsl[t]) {
                    flg[j] = t;
                    break;
                }
        }
        for (j = t = 0; j < frm; j++) if (flg[t] > flg[j]) t = j;
        a++;
        b++;
        prl[i] = ram[t];
        ram[t] = rsl[i];
        for (j = 0; j < frm; j++) mor[j][i] = ram[j];
    }
    cout << endl << endl << " PR:|";
    for (int i = 0; rsl[i] >= 0 && i < 25; i++) {
        if (prl[i] >= 0) cout << prl[i] << "|";
        else cout << " |";
    }
    cout << endl << endl << " RS:|";
    for (int i = 0; rsl[i] >= 0 && i < 25; i++) cout << rsl[i] << "|";
    cout << endl << endl << "RAM:|";
    for (int j = 0; j < frm; j++) {
        if (j) cout << "    |";
        for (int i = 0; rsl[i] >= 0 && i < 25; i++) {
            if (mor[j][i] >= 0) cout << mor[j][i] << "|";
            else cout << " |";
        }
        cout << endl;
    }
    cout << endl << " PF =" << a << endl;
    cout << endl << " PR =" << b << endl;
    cout << endl << "Pages to be replaced" << endl << "list:";
    t = b;
    for (int i = 0; rsl[i] >= 0 && i < 25; i++)
        if (prl[i] >= 0) {
            if (t - b) cout << ",";
            t--;
            cout << prl[i];
        }
}

void sub5() {
    int step = 30, scan = 0, trk[30], odr[31], dir, now, num = 0, pnt = 0, cnt = 1, t = 0;
    double asl = 0;
    cout << "输入N值和调度算法标志(SCAN输入0,CSCAN输入1),空格间隔" << endl;
    cin >> step >> scan;
    cout << "输入磁头已完成请求磁道号和正在服务磁道号,空格间隔" << endl;
    cin >> dir >> now;
    dir = now < dir ? 0 : 1;
    odr[0] = now;
    cout << "依次输入磁道访问请求队列,空格间隔,最后不要带空格,只有换行" << endl;
    for (int i = 0; cin >> trk[i]; num++, i++) if (getchar() == '\n') break;
    num++;
    while (pnt < num) {
        sort(trk + pnt, trk + pnt + min(step, num - pnt));
        for (t = pnt; t < pnt + min(step, num - pnt); t++) if (now < trk[t]) break;
        if (dir) {
            for (int i = t; i < pnt + min(step, num - pnt); i++) odr[cnt++] = trk[i];
            if (scan) for (int i = pnt; i < t; i++) odr[cnt++] = now = trk[i];
            else {
                for (int i = t - 1; i >= pnt; i--) odr[cnt++] = now = trk[i];
                dir = !dir;
            }
        } else {
            for (int i = t - 1; i >= pnt; i--) odr[cnt++] = trk[i];
            if (scan) for (int i = pnt + min(step, num - pnt) - 1; i >= t; i--) odr[cnt++] = now = trk[i];
            else {
                for (int i = t; i < pnt + min(step, num - pnt); i++) odr[cnt++] = now = trk[i];
                dir = !dir;
            }
        }
        pnt += step;
    }
    cout << endl << "磁道访问序列如下:" << endl << "List: ";
    for (int i = 1; i < num; i++) cout << odr[i] << ",";
    cout << odr[num] << endl;
    cout << endl << "平均寻道长度如下:" << endl << "      ";
    t = 0;
    for (int i = 1; i < num; i++)
        if (odr[i] < odr[i - 1] && odr[i] < odr[i + 1] || odr[i] > odr[i - 1] && odr[i] > odr[i + 1]) {
            cout << "(" << max(odr[t], odr[i]) << "-" << min(odr[t], odr[i]) << ")+";
            asl += abs(odr[t] - odr[i]);
            t = i;
        }
    cout << "(" << max(odr[t], odr[num]) << "-" << min(odr[t], odr[num]) << ")";
    asl += abs(odr[t] - odr[num]);
    asl /= num;
    cout << endl << "ASL = ------------------------------------------" << endl << "                    " << num << endl;
    printf("    = %.2lf", asl);
}

string sub6_aux(long long t) {
    string s;
    if (t >= pow(1024, 3)) s = to_string(t / pow(1024, 3) * 1.0).append("G");
    else if (t >= pow(1024, 2)) s = to_string(t / pow(1024, 2) * 1.0).append("M");
    else if (t >= 1024) s = to_string(t / pow(1024, 1) * 1.0).append("K");
    else s = to_string(t * 1.0);
    while (s[s.size() - 2] == '0') s.erase(s.size() - 2, 1);
    if (s[s.size() - 2] == '.') s.erase(s.size() - 2, 1);
    return s;
}

void sub6() {
    string s = "";
    int nd0, nd1, nd2, dzx, cpw, syk, sjk;
    cout << "依次输入直接+一级间接+二级间接地址索引项数目,一行三值,空格间隔" << endl;
    cin >> nd0 >> nd1 >> nd2;
    cout << "依次输入地址项大小(Byte数,输入非正则取默认4Byte)+磁盘ID位数(bit数),空格间隔" << endl;
    cin >> dzx >> cpw;
    dzx = dzx <= 0 ? 4 : dzx;
    cout << "依次输入索引块大小(Byte数)和数据块大小(Byte数,输入非正则取默认与索引块大小相等),空格间隔" << endl;
    cin >> syk >> sjk;
    sjk = sjk <= 0 ? syk : sjk;
    cout.setf(std::ios::left);
    cout << endl;
    cout.width(30);
    cout << s.append(" L0 =").append(to_string(nd0)).append("*").append(to_string(sjk));
    cout << "=";
    s = "";
    printf("%10s\n", sub6_aux(nd0 * pow(syk / dzx, 0) * sjk).c_str());
    cout.width(30);
    cout << s.append(" L1 =").append(to_string(nd1)).append("*").append(to_string(syk)).append("/").append(
            to_string(dzx)).append("*").append(to_string(sjk));
    cout << "=";
    s = "";
    printf("%10s\n", sub6_aux(nd1 * pow(syk / dzx, 1) * sjk).c_str());
    cout.width(30);
    cout << s.append(" L2 =").append(to_string(nd2)).append("*").append(to_string(syk)).append("/").append(
            to_string(dzx)).append("*").append(to_string(syk)).append("/").append(to_string(dzx)).append("*").append(
            to_string(sjk));
    cout << "=";
    s = "";
    printf("%10s\n", sub6_aux(nd2 * pow(syk / dzx, 2) * sjk).c_str());
    cout << endl << "MaxL=L0+L1+L2" << endl << "    =" << sub6_aux(nd0 * pow(syk / dzx, 0) * sjk).c_str() << "+"
         << sub6_aux(nd1 * pow(syk / dzx, 1) * sjk).c_str() << "+" << sub6_aux(nd2 * pow(syk / dzx, 2) * sjk).c_str()
         << endl;
    cout << endl << "MaxP=pow(2," << dzx << "*8-" << cpw << ")*" << sjk << endl << "    ="
         << sub6_aux(pow(2, dzx * 8 - cpw) * sjk);
}

void go() {
    system("color 70");
    system("title STAC");
    int n = 0;
    cout << "本程序仅供参考学习,健壮度没有优化,输入错误可能导致崩溃,重启程序重新输入即可";
    while (1) {
        cout << endl << "输入专题号(1-6)进入该专题核心算法辅助程序,其他数字仅清理屏幕" << endl;
        cin >> n;
        switch (n) {
            case 1:
                system("CLS");
                sub1();
                break;
            case 2:
                system("CLS");
                sub2();
                break;
            case 3:
                system("CLS");
                sub3();
                break;
            case 4:
                system("CLS");
                sub4();
                break;
            case 5:
                system("CLS");
                sub5();
                break;
            case 6:
                system("CLS");
                sub6();
                break;
            default:
                system("CLS");
                break;
        }
    }
}

int main() {
    int W = 1;
    while (W--) go();
    return 0;
}