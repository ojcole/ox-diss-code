OPENQASM 2.0;
include "qelib1.inc";
qreg reg[10];
u3(pi/2,0,pi) reg[0];
u3(pi/2,0,pi) reg[1];
u3(pi/2,0,pi) reg[2];
u3(pi/2,0,pi) reg[3];
u3(pi/2,0,pi) reg[4];
u3(pi/2,0,pi) reg[5];
u3(pi/2,0,pi) reg[6];
u3(pi/2,0,pi) reg[7];
u3(pi/2,0,pi) reg[8];
u3(pi/2,0,pi) reg[9];
u3(0,0,-0.300000011920929) reg[0];
u3(0,0,0.300000011920929) reg[1];
u3(0,0,0.300000011920929) reg[1];
cx reg[0],reg[1];
u3(0,0,-0.300000011920929) reg[1];
cx reg[0],reg[1];
u3(0,0,-0.360000014305115) reg[2];
u3(0,0,0.360000014305115) reg[3];
u3(0,0,0.360000014305115) reg[3];
cx reg[2],reg[3];
u3(0,0,-0.360000014305115) reg[3];
cx reg[2],reg[3];
u3(0,0,-0.119999997317791) reg[4];
u3(0,0,0.119999997317791) reg[5];
u3(0,0,0.119999997317791) reg[5];
cx reg[4],reg[5];
u3(0,0,-0.119999997317791) reg[5];
cx reg[4],reg[5];
u3(0,0,0.219999998807907) reg[6];
u3(0,0,-0.219999998807907) reg[7];
u3(0,0,-0.219999998807907) reg[7];
cx reg[6],reg[7];
u3(0,0,0.219999998807907) reg[7];
cx reg[6],reg[7];
u3(0,0,0.0799999982118607) reg[8];
u3(0,0,-0.0799999982118607) reg[9];
u3(0,0,-0.0799999982118607) reg[9];
cx reg[8],reg[9];
u3(0,0,0.0799999982118607) reg[9];
cx reg[8],reg[9];
u3(0,0,0.259999990463257) reg[1];
u3(0,0,-0.259999990463257) reg[2];
u3(0,0,-0.259999990463257) reg[2];
cx reg[1],reg[2];
u3(0,0,0.259999990463257) reg[2];
cx reg[1],reg[2];
u3(0,0,-0.259999990463257) reg[3];
u3(0,0,0.259999990463257) reg[4];
u3(0,0,0.259999990463257) reg[4];
cx reg[3],reg[4];
u3(0,0,-0.259999990463257) reg[4];
cx reg[3],reg[4];
u3(0,0,0.379999995231628) reg[5];
u3(0,0,-0.379999995231628) reg[6];
u3(0,0,-0.379999995231628) reg[6];
cx reg[5],reg[6];
u3(0,0,0.379999995231628) reg[6];
cx reg[5],reg[6];
u3(0,0,-0.259999990463257) reg[7];
u3(0,0,0.259999990463257) reg[8];
u3(0,0,0.259999990463257) reg[8];
cx reg[7],reg[8];
u3(0,0,-0.259999990463257) reg[8];
cx reg[7],reg[8];
u3(pi/2,0,pi) reg[0];
u3(0,0,-1.91999995708466) reg[0];
u3(pi/2,0,pi) reg[0];
u3(0,0,-0.287999987602234) reg[0];
u3(pi/2,0,pi) reg[1];
u3(0,0,-1.91999995708466) reg[1];
u3(pi/2,0,pi) reg[1];
u3(0,0,0.864000022411346) reg[1];
u3(pi/2,0,pi) reg[2];
u3(0,0,-1.91999995708466) reg[2];
u3(pi/2,0,pi) reg[2];
u3(0,0,1.15199995040894) reg[2];
u3(pi/2,0,pi) reg[3];
u3(0,0,-1.91999995708466) reg[3];
u3(pi/2,0,pi) reg[3];
u3(0,0,-1.05599999427795) reg[3];
u3(pi/2,0,pi) reg[4];
u3(0,0,-1.91999995708466) reg[4];
u3(pi/2,0,pi) reg[4];
u3(0,0,-1.44000005722046) reg[4];
u3(pi/2,0,pi) reg[5];
u3(0,0,-1.91999995708466) reg[5];
u3(pi/2,0,pi) reg[5];
u3(0,0,-0.575999975204468) reg[5];
u3(pi/2,0,pi) reg[6];
u3(0,0,-1.91999995708466) reg[6];
u3(pi/2,0,pi) reg[6];
u3(0,0,1.53600001335144) reg[6];
u3(pi/2,0,pi) reg[7];
u3(0,0,-1.91999995708466) reg[7];
u3(pi/2,0,pi) reg[7];
u3(0,0,-0.287999987602234) reg[7];
u3(pi/2,0,pi) reg[8];
u3(0,0,-1.91999995708466) reg[8];
u3(pi/2,0,pi) reg[8];
u3(0,0,1.24800002574921) reg[8];
u3(pi/2,0,pi) reg[9];
u3(0,0,-1.91999995708466) reg[9];
u3(pi/2,0,pi) reg[9];
u3(0,0,-1.82400000095367) reg[9];
u3(0,0,-0.899999976158142) reg[0];
u3(0,0,0.899999976158142) reg[1];
u3(0,0,0.899999976158142) reg[1];
cx reg[0],reg[1];
u3(0,0,-0.899999976158142) reg[1];
cx reg[0],reg[1];
u3(0,0,-1.08000004291534) reg[2];
u3(0,0,1.08000004291534) reg[3];
u3(0,0,1.08000004291534) reg[3];
cx reg[2],reg[3];
u3(0,0,-1.08000004291534) reg[3];
cx reg[2],reg[3];
u3(0,0,-0.360000014305115) reg[4];
u3(0,0,0.360000014305115) reg[5];
u3(0,0,0.360000014305115) reg[5];
cx reg[4],reg[5];
u3(0,0,-0.360000014305115) reg[5];
cx reg[4],reg[5];
u3(0,0,0.660000026226044) reg[6];
u3(0,0,-0.660000026226044) reg[7];
u3(0,0,-0.660000026226044) reg[7];
cx reg[6],reg[7];
u3(0,0,0.660000026226044) reg[7];
cx reg[6],reg[7];
u3(0,0,0.239999994635582) reg[8];
u3(0,0,-0.239999994635582) reg[9];
u3(0,0,-0.239999994635582) reg[9];
cx reg[8],reg[9];
u3(0,0,0.239999994635582) reg[9];
cx reg[8],reg[9];
u3(0,0,0.779999971389771) reg[1];
u3(0,0,-0.779999971389771) reg[2];
u3(0,0,-0.779999971389771) reg[2];
cx reg[1],reg[2];
u3(0,0,0.779999971389771) reg[2];
cx reg[1],reg[2];
u3(0,0,-0.779999971389771) reg[3];
u3(0,0,0.779999971389771) reg[4];
u3(0,0,0.779999971389771) reg[4];
cx reg[3],reg[4];
u3(0,0,-0.779999971389771) reg[4];
cx reg[3],reg[4];
u3(0,0,1.13999998569489) reg[5];
u3(0,0,-1.13999998569489) reg[6];
u3(0,0,-1.13999998569489) reg[6];
cx reg[5],reg[6];
u3(0,0,1.13999998569489) reg[6];
cx reg[5],reg[6];
u3(0,0,-0.779999971389771) reg[7];
u3(0,0,0.779999971389771) reg[8];
u3(0,0,0.779999971389771) reg[8];
cx reg[7],reg[8];
u3(0,0,-0.779999971389771) reg[8];
cx reg[7],reg[8];
u3(pi/2,0,pi) reg[0];
u3(0,0,-0.959999978542328) reg[0];
u3(pi/2,0,pi) reg[0];
u3(0,0,-0.143999993801117) reg[0];
u3(pi/2,0,pi) reg[1];
u3(0,0,-0.959999978542328) reg[1];
u3(pi/2,0,pi) reg[1];
u3(0,0,0.432000011205673) reg[1];
u3(pi/2,0,pi) reg[2];
u3(0,0,-0.959999978542328) reg[2];
u3(pi/2,0,pi) reg[2];
u3(0,0,0.575999975204468) reg[2];
u3(pi/2,0,pi) reg[3];
u3(0,0,-0.959999978542328) reg[3];
u3(pi/2,0,pi) reg[3];
u3(0,0,-0.527999997138977) reg[3];
u3(pi/2,0,pi) reg[4];
u3(0,0,-0.959999978542328) reg[4];
u3(pi/2,0,pi) reg[4];
u3(0,0,-0.720000028610229) reg[4];
u3(pi/2,0,pi) reg[5];
u3(0,0,-0.959999978542328) reg[5];
u3(pi/2,0,pi) reg[5];
u3(0,0,-0.287999987602234) reg[5];
u3(pi/2,0,pi) reg[6];
u3(0,0,-0.959999978542328) reg[6];
u3(pi/2,0,pi) reg[6];
u3(0,0,0.76800000667572) reg[6];
u3(pi/2,0,pi) reg[7];
u3(0,0,-0.959999978542328) reg[7];
u3(pi/2,0,pi) reg[7];
u3(0,0,-0.143999993801117) reg[7];
u3(pi/2,0,pi) reg[8];
u3(0,0,-0.959999978542328) reg[8];
u3(pi/2,0,pi) reg[8];
u3(0,0,0.624000012874603) reg[8];
u3(pi/2,0,pi) reg[9];
u3(0,0,-0.959999978542328) reg[9];
u3(pi/2,0,pi) reg[9];
u3(0,0,-0.912000000476837) reg[9];
u3(0,0,-1.5) reg[0];
u3(0,0,1.5) reg[1];
u3(0,0,1.5) reg[1];
cx reg[0],reg[1];
u3(0,0,-1.5) reg[1];
cx reg[0],reg[1];
u3(0,0,-1.79999995231628) reg[2];
u3(0,0,1.79999995231628) reg[3];
u3(0,0,1.79999995231628) reg[3];
cx reg[2],reg[3];
u3(0,0,-1.79999995231628) reg[3];
cx reg[2],reg[3];
u3(0,0,-0.600000023841858) reg[4];
u3(0,0,0.600000023841858) reg[5];
u3(0,0,0.600000023841858) reg[5];
cx reg[4],reg[5];
u3(0,0,-0.600000023841858) reg[5];
cx reg[4],reg[5];
u3(0,0,1.10000002384186) reg[6];
u3(0,0,-1.10000002384186) reg[7];
u3(0,0,-1.10000002384186) reg[7];
cx reg[6],reg[7];
u3(0,0,1.10000002384186) reg[7];
cx reg[6],reg[7];
u3(0,0,0.400000005960464) reg[8];
u3(0,0,-0.400000005960464) reg[9];
u3(0,0,-0.400000005960464) reg[9];
cx reg[8],reg[9];
u3(0,0,0.400000005960464) reg[9];
cx reg[8],reg[9];
u3(0,0,1.29999995231628) reg[1];
u3(0,0,-1.29999995231628) reg[2];
u3(0,0,-1.29999995231628) reg[2];
cx reg[1],reg[2];
u3(0,0,1.29999995231628) reg[2];
cx reg[1],reg[2];
u3(0,0,-1.29999995231628) reg[3];
u3(0,0,1.29999995231628) reg[4];
u3(0,0,1.29999995231628) reg[4];
cx reg[3],reg[4];
u3(0,0,-1.29999995231628) reg[4];
cx reg[3],reg[4];
u3(0,0,1.89999997615814) reg[5];
u3(0,0,-1.89999997615814) reg[6];
u3(0,0,-1.89999997615814) reg[6];
cx reg[5],reg[6];
u3(0,0,1.89999997615814) reg[6];
cx reg[5],reg[6];
u3(0,0,-1.29999995231628) reg[7];
u3(0,0,1.29999995231628) reg[8];
u3(0,0,1.29999995231628) reg[8];
cx reg[7],reg[8];
u3(0,0,-1.29999995231628) reg[8];
cx reg[7],reg[8];
u3(pi/2,0,pi) reg[0];
u3(0,0,0) reg[0];
u3(pi/2,0,pi) reg[0];
u3(0,0,0) reg[0];
u3(pi/2,0,pi) reg[1];
u3(0,0,0) reg[1];
u3(pi/2,0,pi) reg[1];
u3(0,0,0) reg[1];
u3(pi/2,0,pi) reg[2];
u3(0,0,0) reg[2];
u3(pi/2,0,pi) reg[2];
u3(0,0,0) reg[2];
u3(pi/2,0,pi) reg[3];
u3(0,0,0) reg[3];
u3(pi/2,0,pi) reg[3];
u3(0,0,0) reg[3];
u3(pi/2,0,pi) reg[4];
u3(0,0,0) reg[4];
u3(pi/2,0,pi) reg[4];
u3(0,0,0) reg[4];
u3(pi/2,0,pi) reg[5];
u3(0,0,0) reg[5];
u3(pi/2,0,pi) reg[5];
u3(0,0,0) reg[5];
u3(pi/2,0,pi) reg[6];
u3(0,0,0) reg[6];
u3(pi/2,0,pi) reg[6];
u3(0,0,0) reg[6];
u3(pi/2,0,pi) reg[7];
u3(0,0,0) reg[7];
u3(pi/2,0,pi) reg[7];
u3(0,0,0) reg[7];
u3(pi/2,0,pi) reg[8];
u3(0,0,0) reg[8];
u3(pi/2,0,pi) reg[8];
u3(0,0,0) reg[8];
u3(pi/2,0,pi) reg[9];
u3(0,0,0) reg[9];
u3(pi/2,0,pi) reg[9];
u3(0,0,0) reg[9];
u3(0,0,-2.09999990463257) reg[0];
u3(0,0,2.09999990463257) reg[1];
u3(0,0,2.09999990463257) reg[1];
cx reg[0],reg[1];
u3(0,0,-2.09999990463257) reg[1];
cx reg[0],reg[1];
u3(0,0,-2.51999998092651) reg[2];
u3(0,0,2.51999998092651) reg[3];
u3(0,0,2.51999998092651) reg[3];
cx reg[2],reg[3];
u3(0,0,-2.51999998092651) reg[3];
cx reg[2],reg[3];
u3(0,0,-0.839999973773956) reg[4];
u3(0,0,0.839999973773956) reg[5];
u3(0,0,0.839999973773956) reg[5];
cx reg[4],reg[5];
u3(0,0,-0.839999973773956) reg[5];
cx reg[4],reg[5];
u3(0,0,1.53999996185303) reg[6];
u3(0,0,-1.53999996185303) reg[7];
u3(0,0,-1.53999996185303) reg[7];
cx reg[6],reg[7];
u3(0,0,1.53999996185303) reg[7];
cx reg[6],reg[7];
u3(0,0,0.560000002384186) reg[8];
u3(0,0,-0.560000002384186) reg[9];
u3(0,0,-0.560000002384186) reg[9];
cx reg[8],reg[9];
u3(0,0,0.560000002384186) reg[9];
cx reg[8],reg[9];
u3(0,0,1.82000005245209) reg[1];
u3(0,0,-1.82000005245209) reg[2];
u3(0,0,-1.82000005245209) reg[2];
cx reg[1],reg[2];
u3(0,0,1.82000005245209) reg[2];
cx reg[1],reg[2];
u3(0,0,-1.82000005245209) reg[3];
u3(0,0,1.82000005245209) reg[4];
u3(0,0,1.82000005245209) reg[4];
cx reg[3],reg[4];
u3(0,0,-1.82000005245209) reg[4];
cx reg[3],reg[4];
u3(0,0,2.66000008583069) reg[5];
u3(0,0,-2.66000008583069) reg[6];
u3(0,0,-2.66000008583069) reg[6];
cx reg[5],reg[6];
u3(0,0,2.66000008583069) reg[6];
cx reg[5],reg[6];
u3(0,0,-1.82000005245209) reg[7];
u3(0,0,1.82000005245209) reg[8];
u3(0,0,1.82000005245209) reg[8];
cx reg[7],reg[8];
u3(0,0,-1.82000005245209) reg[8];
cx reg[7],reg[8];
u3(pi/2,0,pi) reg[0];
u3(0,0,0.959999978542328) reg[0];
u3(pi/2,0,pi) reg[0];
u3(0,0,0.143999993801117) reg[0];
u3(pi/2,0,pi) reg[1];
u3(0,0,0.959999978542328) reg[1];
u3(pi/2,0,pi) reg[1];
u3(0,0,-0.432000011205673) reg[1];
u3(pi/2,0,pi) reg[2];
u3(0,0,0.959999978542328) reg[2];
u3(pi/2,0,pi) reg[2];
u3(0,0,-0.575999975204468) reg[2];
u3(pi/2,0,pi) reg[3];
u3(0,0,0.959999978542328) reg[3];
u3(pi/2,0,pi) reg[3];
u3(0,0,0.527999997138977) reg[3];
u3(pi/2,0,pi) reg[4];
u3(0,0,0.959999978542328) reg[4];
u3(pi/2,0,pi) reg[4];
u3(0,0,0.720000028610229) reg[4];
u3(pi/2,0,pi) reg[5];
u3(0,0,0.959999978542328) reg[5];
u3(pi/2,0,pi) reg[5];
u3(0,0,0.287999987602234) reg[5];
u3(pi/2,0,pi) reg[6];
u3(0,0,0.959999978542328) reg[6];
u3(pi/2,0,pi) reg[6];
u3(0,0,-0.76800000667572) reg[6];
u3(pi/2,0,pi) reg[7];
u3(0,0,0.959999978542328) reg[7];
u3(pi/2,0,pi) reg[7];
u3(0,0,0.143999993801117) reg[7];
u3(pi/2,0,pi) reg[8];
u3(0,0,0.959999978542328) reg[8];
u3(pi/2,0,pi) reg[8];
u3(0,0,-0.624000012874603) reg[8];
u3(pi/2,0,pi) reg[9];
u3(0,0,0.959999978542328) reg[9];
u3(pi/2,0,pi) reg[9];
u3(0,0,0.912000000476837) reg[9];
u3(0,0,-2.70000004768372) reg[0];
u3(0,0,2.70000004768372) reg[1];
u3(0,0,2.70000004768372) reg[1];
cx reg[0],reg[1];
u3(0,0,-2.70000004768372) reg[1];
cx reg[0],reg[1];
u3(0,0,-3.24000000953674) reg[2];
u3(0,0,3.24000000953674) reg[3];
u3(0,0,3.24000000953674) reg[3];
cx reg[2],reg[3];
u3(0,0,-3.24000000953674) reg[3];
cx reg[2],reg[3];
u3(0,0,-1.08000004291534) reg[4];
u3(0,0,1.08000004291534) reg[5];
u3(0,0,1.08000004291534) reg[5];
cx reg[4],reg[5];
u3(0,0,-1.08000004291534) reg[5];
cx reg[4],reg[5];
u3(0,0,1.98000001907349) reg[6];
u3(0,0,-1.98000001907349) reg[7];
u3(0,0,-1.98000001907349) reg[7];
cx reg[6],reg[7];
u3(0,0,1.98000001907349) reg[7];
cx reg[6],reg[7];
u3(0,0,0.720000028610229) reg[8];
u3(0,0,-0.720000028610229) reg[9];
u3(0,0,-0.720000028610229) reg[9];
cx reg[8],reg[9];
u3(0,0,0.720000028610229) reg[9];
cx reg[8],reg[9];
u3(0,0,2.33999991416931) reg[1];
u3(0,0,-2.33999991416931) reg[2];
u3(0,0,-2.33999991416931) reg[2];
cx reg[1],reg[2];
u3(0,0,2.33999991416931) reg[2];
cx reg[1],reg[2];
u3(0,0,-2.33999991416931) reg[3];
u3(0,0,2.33999991416931) reg[4];
u3(0,0,2.33999991416931) reg[4];
cx reg[3],reg[4];
u3(0,0,-2.33999991416931) reg[4];
cx reg[3],reg[4];
u3(0,0,3.42000007629395) reg[5];
u3(0,0,-3.42000007629395) reg[6];
u3(0,0,-3.42000007629395) reg[6];
cx reg[5],reg[6];
u3(0,0,3.42000007629395) reg[6];
cx reg[5],reg[6];
u3(0,0,-2.33999991416931) reg[7];
u3(0,0,2.33999991416931) reg[8];
u3(0,0,2.33999991416931) reg[8];
cx reg[7],reg[8];
u3(0,0,-2.33999991416931) reg[8];
cx reg[7],reg[8];
u3(pi/2,0,pi) reg[0];
u3(0,0,1.91999995708466) reg[0];
u3(pi/2,0,pi) reg[0];
u3(0,0,0.287999987602234) reg[0];
u3(pi/2,0,pi) reg[1];
u3(0,0,1.91999995708466) reg[1];
u3(pi/2,0,pi) reg[1];
u3(0,0,-0.864000022411346) reg[1];
u3(pi/2,0,pi) reg[2];
u3(0,0,1.91999995708466) reg[2];
u3(pi/2,0,pi) reg[2];
u3(0,0,-1.15199995040894) reg[2];
u3(pi/2,0,pi) reg[3];
u3(0,0,1.91999995708466) reg[3];
u3(pi/2,0,pi) reg[3];
u3(0,0,1.05599999427795) reg[3];
u3(pi/2,0,pi) reg[4];
u3(0,0,1.91999995708466) reg[4];
u3(pi/2,0,pi) reg[4];
u3(0,0,1.44000005722046) reg[4];
u3(pi/2,0,pi) reg[5];
u3(0,0,1.91999995708466) reg[5];
u3(pi/2,0,pi) reg[5];
u3(0,0,0.575999975204468) reg[5];
u3(pi/2,0,pi) reg[6];
u3(0,0,1.91999995708466) reg[6];
u3(pi/2,0,pi) reg[6];
u3(0,0,-1.53600001335144) reg[6];
u3(pi/2,0,pi) reg[7];
u3(0,0,1.91999995708466) reg[7];
u3(pi/2,0,pi) reg[7];
u3(0,0,0.287999987602234) reg[7];
u3(pi/2,0,pi) reg[8];
u3(0,0,1.91999995708466) reg[8];
u3(pi/2,0,pi) reg[8];
u3(0,0,-1.24800002574921) reg[8];
u3(pi/2,0,pi) reg[9];
u3(0,0,1.91999995708466) reg[9];
u3(pi/2,0,pi) reg[9];
u3(0,0,1.82400000095367) reg[9];