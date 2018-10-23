
/*
 * PPDL gdb server stub
 * Copyright (c) 2014 Maxim Perov <coder@frtk.ru>
 */

#pragma GCC diagnostic ignored "-Wreturn-type"
#include "config.h"
#include "qemu-common.h"
#include "exec/gdbstub.h"

int ppdl_cpu_gdb_read_register(CPUState *cs, uint8_t *mem_buf, int reg) {
	PPDLCPU *cpu = PPDL_CPU(cs);
	CPUPPDLState *env = &cpu->env;
	switch (reg) {
		case 0:
			return gdb_get_reg32(mem_buf, env->pc);
			break;
		case 1:
			return gdb_get_reg64(mem_buf, env->cur_addr);
			break;
		case 2:
			return gdb_get_reg64(mem_buf, env->caller_addr);
			break;
		case 3:
			return gdb_get_reg64(mem_buf, env->origin_addr);
			break;
		case 4:
			return gdb_get_reg32(mem_buf, env->gas_price);
			break;
		case 5:
			return gdb_get_reg64(mem_buf, env->ext_code_size);
			break;
		case 6:
			return gdb_get_reg64(mem_buf, env->inp_data_size);
			break;
		case 7:
			return gdb_get_reg32(mem_buf, env->log_ptr);
			break;
		case 8:
			return gdb_get_reg32(mem_buf, env->sp);
			break;
		case 9:
			return gdb_get_reg32(mem_buf, env->gas_available);
			break;
		case 10:
			return gdb_get_reg8(mem_buf, env->data_bus[0]);
			break;
		case 11:
			return gdb_get_reg8(mem_buf, env->data_bus[1]);
			break;
		case 12:
			return gdb_get_reg8(mem_buf, env->data_bus[2]);
			break;
		case 13:
			return gdb_get_reg8(mem_buf, env->data_bus[3]);
			break;
		case 14:
			return gdb_get_reg8(mem_buf, env->data_bus[4]);
			break;
		case 15:
			return gdb_get_reg8(mem_buf, env->data_bus[5]);
			break;
		case 16:
			return gdb_get_reg8(mem_buf, env->data_bus[6]);
			break;
		case 17:
			return gdb_get_reg8(mem_buf, env->data_bus[7]);
			break;
		case 18:
			return gdb_get_reg8(mem_buf, env->data_bus[8]);
			break;
		case 19:
			return gdb_get_reg8(mem_buf, env->data_bus[9]);
			break;
		case 20:
			return gdb_get_reg8(mem_buf, env->data_bus[10]);
			break;
		case 21:
			return gdb_get_reg8(mem_buf, env->data_bus[11]);
			break;
		case 22:
			return gdb_get_reg8(mem_buf, env->data_bus[12]);
			break;
		case 23:
			return gdb_get_reg8(mem_buf, env->data_bus[13]);
			break;
		case 24:
			return gdb_get_reg8(mem_buf, env->data_bus[14]);
			break;
		case 25:
			return gdb_get_reg8(mem_buf, env->data_bus[15]);
			break;
		case 26:
			return gdb_get_reg8(mem_buf, env->data_bus[16]);
			break;
		case 27:
			return gdb_get_reg8(mem_buf, env->data_bus[17]);
			break;
		case 28:
			return gdb_get_reg8(mem_buf, env->data_bus[18]);
			break;
		case 29:
			return gdb_get_reg8(mem_buf, env->data_bus[19]);
			break;
		case 30:
			return gdb_get_reg8(mem_buf, env->data_bus[20]);
			break;
		case 31:
			return gdb_get_reg8(mem_buf, env->data_bus[21]);
			break;
		case 32:
			return gdb_get_reg8(mem_buf, env->data_bus[22]);
			break;
		case 33:
			return gdb_get_reg8(mem_buf, env->data_bus[23]);
			break;
		case 34:
			return gdb_get_reg8(mem_buf, env->data_bus[24]);
			break;
		case 35:
			return gdb_get_reg8(mem_buf, env->data_bus[25]);
			break;
		case 36:
			return gdb_get_reg8(mem_buf, env->data_bus[26]);
			break;
		case 37:
			return gdb_get_reg8(mem_buf, env->data_bus[27]);
			break;
		case 38:
			return gdb_get_reg8(mem_buf, env->data_bus[28]);
			break;
		case 39:
			return gdb_get_reg8(mem_buf, env->data_bus[29]);
			break;
		case 40:
			return gdb_get_reg8(mem_buf, env->data_bus[30]);
			break;
		case 41:
			return gdb_get_reg8(mem_buf, env->data_bus[31]);
			break;
		case 42:
			return gdb_get_reg8(mem_buf, env->data_bus[32]);
			break;
		case 43:
			return gdb_get_reg8(mem_buf, env->data_bus[33]);
			break;
		case 44:
			return gdb_get_reg8(mem_buf, env->data_bus[34]);
			break;
		case 45:
			return gdb_get_reg8(mem_buf, env->data_bus[35]);
			break;
		case 46:
			return gdb_get_reg8(mem_buf, env->data_bus[36]);
			break;
		case 47:
			return gdb_get_reg8(mem_buf, env->data_bus[37]);
			break;
		case 48:
			return gdb_get_reg8(mem_buf, env->data_bus[38]);
			break;
		case 49:
			return gdb_get_reg8(mem_buf, env->data_bus[39]);
			break;
		case 50:
			return gdb_get_reg8(mem_buf, env->data_bus[40]);
			break;
		case 51:
			return gdb_get_reg8(mem_buf, env->data_bus[41]);
			break;
		case 52:
			return gdb_get_reg8(mem_buf, env->data_bus[42]);
			break;
		case 53:
			return gdb_get_reg8(mem_buf, env->data_bus[43]);
			break;
		case 54:
			return gdb_get_reg8(mem_buf, env->data_bus[44]);
			break;
		case 55:
			return gdb_get_reg8(mem_buf, env->data_bus[45]);
			break;
		case 56:
			return gdb_get_reg8(mem_buf, env->data_bus[46]);
			break;
		case 57:
			return gdb_get_reg8(mem_buf, env->data_bus[47]);
			break;
		case 58:
			return gdb_get_reg8(mem_buf, env->data_bus[48]);
			break;
		case 59:
			return gdb_get_reg8(mem_buf, env->data_bus[49]);
			break;
		case 60:
			return gdb_get_reg8(mem_buf, env->data_bus[50]);
			break;
		case 61:
			return gdb_get_reg8(mem_buf, env->data_bus[51]);
			break;
		case 62:
			return gdb_get_reg8(mem_buf, env->data_bus[52]);
			break;
		case 63:
			return gdb_get_reg8(mem_buf, env->data_bus[53]);
			break;
		case 64:
			return gdb_get_reg8(mem_buf, env->data_bus[54]);
			break;
		case 65:
			return gdb_get_reg8(mem_buf, env->data_bus[55]);
			break;
		case 66:
			return gdb_get_reg8(mem_buf, env->data_bus[56]);
			break;
		case 67:
			return gdb_get_reg8(mem_buf, env->data_bus[57]);
			break;
		case 68:
			return gdb_get_reg8(mem_buf, env->data_bus[58]);
			break;
		case 69:
			return gdb_get_reg8(mem_buf, env->data_bus[59]);
			break;
		case 70:
			return gdb_get_reg8(mem_buf, env->data_bus[60]);
			break;
		case 71:
			return gdb_get_reg8(mem_buf, env->data_bus[61]);
			break;
		case 72:
			return gdb_get_reg8(mem_buf, env->data_bus[62]);
			break;
		case 73:
			return gdb_get_reg8(mem_buf, env->data_bus[63]);
			break;
		case 74:
			return gdb_get_reg8(mem_buf, env->data_bus[64]);
			break;
		case 75:
			return gdb_get_reg8(mem_buf, env->data_bus[65]);
			break;
		case 76:
			return gdb_get_reg8(mem_buf, env->data_bus[66]);
			break;
		case 77:
			return gdb_get_reg8(mem_buf, env->data_bus[67]);
			break;
		case 78:
			return gdb_get_reg8(mem_buf, env->data_bus[68]);
			break;
		case 79:
			return gdb_get_reg8(mem_buf, env->data_bus[69]);
			break;
		case 80:
			return gdb_get_reg8(mem_buf, env->data_bus[70]);
			break;
		case 81:
			return gdb_get_reg8(mem_buf, env->data_bus[71]);
			break;
		case 82:
			return gdb_get_reg8(mem_buf, env->data_bus[72]);
			break;
		case 83:
			return gdb_get_reg8(mem_buf, env->data_bus[73]);
			break;
		case 84:
			return gdb_get_reg8(mem_buf, env->data_bus[74]);
			break;
		case 85:
			return gdb_get_reg8(mem_buf, env->data_bus[75]);
			break;
		case 86:
			return gdb_get_reg8(mem_buf, env->data_bus[76]);
			break;
		case 87:
			return gdb_get_reg8(mem_buf, env->data_bus[77]);
			break;
		case 88:
			return gdb_get_reg8(mem_buf, env->data_bus[78]);
			break;
		case 89:
			return gdb_get_reg8(mem_buf, env->data_bus[79]);
			break;
		case 90:
			return gdb_get_reg8(mem_buf, env->data_bus[80]);
			break;
		case 91:
			return gdb_get_reg8(mem_buf, env->data_bus[81]);
			break;
		case 92:
			return gdb_get_reg8(mem_buf, env->data_bus[82]);
			break;
		case 93:
			return gdb_get_reg8(mem_buf, env->data_bus[83]);
			break;
		case 94:
			return gdb_get_reg8(mem_buf, env->data_bus[84]);
			break;
		case 95:
			return gdb_get_reg8(mem_buf, env->data_bus[85]);
			break;
		case 96:
			return gdb_get_reg8(mem_buf, env->data_bus[86]);
			break;
		case 97:
			return gdb_get_reg8(mem_buf, env->data_bus[87]);
			break;
		case 98:
			return gdb_get_reg8(mem_buf, env->data_bus[88]);
			break;
		case 99:
			return gdb_get_reg8(mem_buf, env->data_bus[89]);
			break;
		case 100:
			return gdb_get_reg8(mem_buf, env->data_bus[90]);
			break;
		case 101:
			return gdb_get_reg8(mem_buf, env->data_bus[91]);
			break;
		case 102:
			return gdb_get_reg8(mem_buf, env->data_bus[92]);
			break;
		case 103:
			return gdb_get_reg8(mem_buf, env->data_bus[93]);
			break;
		case 104:
			return gdb_get_reg8(mem_buf, env->data_bus[94]);
			break;
		case 105:
			return gdb_get_reg8(mem_buf, env->data_bus[95]);
			break;
		case 106:
			return gdb_get_reg8(mem_buf, env->data_bus[96]);
			break;
		case 107:
			return gdb_get_reg8(mem_buf, env->data_bus[97]);
			break;
		case 108:
			return gdb_get_reg8(mem_buf, env->data_bus[98]);
			break;
		case 109:
			return gdb_get_reg8(mem_buf, env->data_bus[99]);
			break;
		case 110:
			return gdb_get_reg8(mem_buf, env->data_bus[100]);
			break;
		case 111:
			return gdb_get_reg8(mem_buf, env->data_bus[101]);
			break;
		case 112:
			return gdb_get_reg8(mem_buf, env->data_bus[102]);
			break;
		case 113:
			return gdb_get_reg8(mem_buf, env->data_bus[103]);
			break;
		case 114:
			return gdb_get_reg8(mem_buf, env->data_bus[104]);
			break;
		case 115:
			return gdb_get_reg8(mem_buf, env->data_bus[105]);
			break;
		case 116:
			return gdb_get_reg8(mem_buf, env->data_bus[106]);
			break;
		case 117:
			return gdb_get_reg8(mem_buf, env->data_bus[107]);
			break;
		case 118:
			return gdb_get_reg8(mem_buf, env->data_bus[108]);
			break;
		case 119:
			return gdb_get_reg8(mem_buf, env->data_bus[109]);
			break;
		case 120:
			return gdb_get_reg8(mem_buf, env->data_bus[110]);
			break;
		case 121:
			return gdb_get_reg8(mem_buf, env->data_bus[111]);
			break;
		case 122:
			return gdb_get_reg8(mem_buf, env->data_bus[112]);
			break;
		case 123:
			return gdb_get_reg8(mem_buf, env->data_bus[113]);
			break;
		case 124:
			return gdb_get_reg8(mem_buf, env->data_bus[114]);
			break;
		case 125:
			return gdb_get_reg8(mem_buf, env->data_bus[115]);
			break;
		case 126:
			return gdb_get_reg8(mem_buf, env->data_bus[116]);
			break;
		case 127:
			return gdb_get_reg8(mem_buf, env->data_bus[117]);
			break;
		case 128:
			return gdb_get_reg8(mem_buf, env->data_bus[118]);
			break;
		case 129:
			return gdb_get_reg8(mem_buf, env->data_bus[119]);
			break;
		case 130:
			return gdb_get_reg8(mem_buf, env->data_bus[120]);
			break;
		case 131:
			return gdb_get_reg8(mem_buf, env->data_bus[121]);
			break;
		case 132:
			return gdb_get_reg8(mem_buf, env->data_bus[122]);
			break;
		case 133:
			return gdb_get_reg8(mem_buf, env->data_bus[123]);
			break;
		case 134:
			return gdb_get_reg8(mem_buf, env->data_bus[124]);
			break;
		case 135:
			return gdb_get_reg8(mem_buf, env->data_bus[125]);
			break;
		case 136:
			return gdb_get_reg8(mem_buf, env->data_bus[126]);
			break;
		case 137:
			return gdb_get_reg8(mem_buf, env->data_bus[127]);
			break;
		case 138:
			return gdb_get_reg8(mem_buf, env->data_bus[128]);
			break;
		case 139:
			return gdb_get_reg8(mem_buf, env->data_bus[129]);
			break;
		case 140:
			return gdb_get_reg8(mem_buf, env->data_bus[130]);
			break;
		case 141:
			return gdb_get_reg8(mem_buf, env->data_bus[131]);
			break;
		case 142:
			return gdb_get_reg8(mem_buf, env->data_bus[132]);
			break;
		case 143:
			return gdb_get_reg8(mem_buf, env->data_bus[133]);
			break;
		case 144:
			return gdb_get_reg8(mem_buf, env->data_bus[134]);
			break;
		case 145:
			return gdb_get_reg8(mem_buf, env->data_bus[135]);
			break;
		case 146:
			return gdb_get_reg8(mem_buf, env->data_bus[136]);
			break;
		case 147:
			return gdb_get_reg8(mem_buf, env->data_bus[137]);
			break;
		case 148:
			return gdb_get_reg8(mem_buf, env->data_bus[138]);
			break;
		case 149:
			return gdb_get_reg8(mem_buf, env->data_bus[139]);
			break;
		case 150:
			return gdb_get_reg8(mem_buf, env->data_bus[140]);
			break;
		case 151:
			return gdb_get_reg8(mem_buf, env->data_bus[141]);
			break;
		case 152:
			return gdb_get_reg8(mem_buf, env->data_bus[142]);
			break;
		case 153:
			return gdb_get_reg8(mem_buf, env->data_bus[143]);
			break;
		case 154:
			return gdb_get_reg8(mem_buf, env->data_bus[144]);
			break;
		case 155:
			return gdb_get_reg8(mem_buf, env->data_bus[145]);
			break;
		case 156:
			return gdb_get_reg8(mem_buf, env->data_bus[146]);
			break;
		case 157:
			return gdb_get_reg8(mem_buf, env->data_bus[147]);
			break;
		case 158:
			return gdb_get_reg8(mem_buf, env->data_bus[148]);
			break;
		case 159:
			return gdb_get_reg8(mem_buf, env->data_bus[149]);
			break;
		case 160:
			return gdb_get_reg8(mem_buf, env->data_bus[150]);
			break;
		case 161:
			return gdb_get_reg8(mem_buf, env->data_bus[151]);
			break;
		case 162:
			return gdb_get_reg8(mem_buf, env->data_bus[152]);
			break;
		case 163:
			return gdb_get_reg8(mem_buf, env->data_bus[153]);
			break;
		case 164:
			return gdb_get_reg8(mem_buf, env->data_bus[154]);
			break;
		case 165:
			return gdb_get_reg8(mem_buf, env->data_bus[155]);
			break;
		case 166:
			return gdb_get_reg8(mem_buf, env->data_bus[156]);
			break;
		case 167:
			return gdb_get_reg8(mem_buf, env->data_bus[157]);
			break;
		case 168:
			return gdb_get_reg8(mem_buf, env->data_bus[158]);
			break;
		case 169:
			return gdb_get_reg8(mem_buf, env->data_bus[159]);
			break;
		case 170:
			return gdb_get_reg8(mem_buf, env->data_bus[160]);
			break;
		case 171:
			return gdb_get_reg8(mem_buf, env->data_bus[161]);
			break;
		case 172:
			return gdb_get_reg8(mem_buf, env->data_bus[162]);
			break;
		case 173:
			return gdb_get_reg8(mem_buf, env->data_bus[163]);
			break;
		case 174:
			return gdb_get_reg8(mem_buf, env->data_bus[164]);
			break;
		case 175:
			return gdb_get_reg8(mem_buf, env->data_bus[165]);
			break;
		case 176:
			return gdb_get_reg8(mem_buf, env->data_bus[166]);
			break;
		case 177:
			return gdb_get_reg8(mem_buf, env->data_bus[167]);
			break;
		case 178:
			return gdb_get_reg8(mem_buf, env->data_bus[168]);
			break;
		case 179:
			return gdb_get_reg8(mem_buf, env->data_bus[169]);
			break;
		case 180:
			return gdb_get_reg8(mem_buf, env->data_bus[170]);
			break;
		case 181:
			return gdb_get_reg8(mem_buf, env->data_bus[171]);
			break;
		case 182:
			return gdb_get_reg8(mem_buf, env->data_bus[172]);
			break;
		case 183:
			return gdb_get_reg8(mem_buf, env->data_bus[173]);
			break;
		case 184:
			return gdb_get_reg8(mem_buf, env->data_bus[174]);
			break;
		case 185:
			return gdb_get_reg8(mem_buf, env->data_bus[175]);
			break;
		case 186:
			return gdb_get_reg8(mem_buf, env->data_bus[176]);
			break;
		case 187:
			return gdb_get_reg8(mem_buf, env->data_bus[177]);
			break;
		case 188:
			return gdb_get_reg8(mem_buf, env->data_bus[178]);
			break;
		case 189:
			return gdb_get_reg8(mem_buf, env->data_bus[179]);
			break;
		case 190:
			return gdb_get_reg8(mem_buf, env->data_bus[180]);
			break;
		case 191:
			return gdb_get_reg8(mem_buf, env->data_bus[181]);
			break;
		case 192:
			return gdb_get_reg8(mem_buf, env->data_bus[182]);
			break;
		case 193:
			return gdb_get_reg8(mem_buf, env->data_bus[183]);
			break;
		case 194:
			return gdb_get_reg8(mem_buf, env->data_bus[184]);
			break;
		case 195:
			return gdb_get_reg8(mem_buf, env->data_bus[185]);
			break;
		case 196:
			return gdb_get_reg8(mem_buf, env->data_bus[186]);
			break;
		case 197:
			return gdb_get_reg8(mem_buf, env->data_bus[187]);
			break;
		case 198:
			return gdb_get_reg8(mem_buf, env->data_bus[188]);
			break;
		case 199:
			return gdb_get_reg8(mem_buf, env->data_bus[189]);
			break;
		case 200:
			return gdb_get_reg8(mem_buf, env->data_bus[190]);
			break;
		case 201:
			return gdb_get_reg8(mem_buf, env->data_bus[191]);
			break;
		case 202:
			return gdb_get_reg8(mem_buf, env->data_bus[192]);
			break;
		case 203:
			return gdb_get_reg8(mem_buf, env->data_bus[193]);
			break;
		case 204:
			return gdb_get_reg8(mem_buf, env->data_bus[194]);
			break;
		case 205:
			return gdb_get_reg8(mem_buf, env->data_bus[195]);
			break;
		case 206:
			return gdb_get_reg8(mem_buf, env->data_bus[196]);
			break;
		case 207:
			return gdb_get_reg8(mem_buf, env->data_bus[197]);
			break;
		case 208:
			return gdb_get_reg8(mem_buf, env->data_bus[198]);
			break;
		case 209:
			return gdb_get_reg8(mem_buf, env->data_bus[199]);
			break;
		case 210:
			return gdb_get_reg8(mem_buf, env->data_bus[200]);
			break;
		case 211:
			return gdb_get_reg8(mem_buf, env->data_bus[201]);
			break;
		case 212:
			return gdb_get_reg8(mem_buf, env->data_bus[202]);
			break;
		case 213:
			return gdb_get_reg8(mem_buf, env->data_bus[203]);
			break;
		case 214:
			return gdb_get_reg8(mem_buf, env->data_bus[204]);
			break;
		case 215:
			return gdb_get_reg8(mem_buf, env->data_bus[205]);
			break;
		case 216:
			return gdb_get_reg8(mem_buf, env->data_bus[206]);
			break;
		case 217:
			return gdb_get_reg8(mem_buf, env->data_bus[207]);
			break;
		case 218:
			return gdb_get_reg8(mem_buf, env->data_bus[208]);
			break;
		case 219:
			return gdb_get_reg8(mem_buf, env->data_bus[209]);
			break;
		case 220:
			return gdb_get_reg8(mem_buf, env->data_bus[210]);
			break;
		case 221:
			return gdb_get_reg8(mem_buf, env->data_bus[211]);
			break;
		case 222:
			return gdb_get_reg8(mem_buf, env->data_bus[212]);
			break;
		case 223:
			return gdb_get_reg8(mem_buf, env->data_bus[213]);
			break;
		case 224:
			return gdb_get_reg8(mem_buf, env->data_bus[214]);
			break;
		case 225:
			return gdb_get_reg8(mem_buf, env->data_bus[215]);
			break;
		case 226:
			return gdb_get_reg8(mem_buf, env->data_bus[216]);
			break;
		case 227:
			return gdb_get_reg8(mem_buf, env->data_bus[217]);
			break;
		case 228:
			return gdb_get_reg8(mem_buf, env->data_bus[218]);
			break;
		case 229:
			return gdb_get_reg8(mem_buf, env->data_bus[219]);
			break;
		case 230:
			return gdb_get_reg8(mem_buf, env->data_bus[220]);
			break;
		case 231:
			return gdb_get_reg8(mem_buf, env->data_bus[221]);
			break;
		case 232:
			return gdb_get_reg8(mem_buf, env->data_bus[222]);
			break;
		case 233:
			return gdb_get_reg8(mem_buf, env->data_bus[223]);
			break;
		case 234:
			return gdb_get_reg8(mem_buf, env->data_bus[224]);
			break;
		case 235:
			return gdb_get_reg8(mem_buf, env->data_bus[225]);
			break;
		case 236:
			return gdb_get_reg8(mem_buf, env->data_bus[226]);
			break;
		case 237:
			return gdb_get_reg8(mem_buf, env->data_bus[227]);
			break;
		case 238:
			return gdb_get_reg8(mem_buf, env->data_bus[228]);
			break;
		case 239:
			return gdb_get_reg8(mem_buf, env->data_bus[229]);
			break;
		case 240:
			return gdb_get_reg8(mem_buf, env->data_bus[230]);
			break;
		case 241:
			return gdb_get_reg8(mem_buf, env->data_bus[231]);
			break;
		case 242:
			return gdb_get_reg8(mem_buf, env->data_bus[232]);
			break;
		case 243:
			return gdb_get_reg8(mem_buf, env->data_bus[233]);
			break;
		case 244:
			return gdb_get_reg8(mem_buf, env->data_bus[234]);
			break;
		case 245:
			return gdb_get_reg8(mem_buf, env->data_bus[235]);
			break;
		case 246:
			return gdb_get_reg8(mem_buf, env->data_bus[236]);
			break;
		case 247:
			return gdb_get_reg8(mem_buf, env->data_bus[237]);
			break;
		case 248:
			return gdb_get_reg8(mem_buf, env->data_bus[238]);
			break;
		case 249:
			return gdb_get_reg8(mem_buf, env->data_bus[239]);
			break;
		case 250:
			return gdb_get_reg8(mem_buf, env->data_bus[240]);
			break;
		case 251:
			return gdb_get_reg8(mem_buf, env->data_bus[241]);
			break;
		case 252:
			return gdb_get_reg8(mem_buf, env->data_bus[242]);
			break;
		case 253:
			return gdb_get_reg8(mem_buf, env->data_bus[243]);
			break;
		case 254:
			return gdb_get_reg8(mem_buf, env->data_bus[244]);
			break;
		case 255:
			return gdb_get_reg8(mem_buf, env->data_bus[245]);
			break;
		case 256:
			return gdb_get_reg8(mem_buf, env->data_bus[246]);
			break;
		case 257:
			return gdb_get_reg8(mem_buf, env->data_bus[247]);
			break;
		case 258:
			return gdb_get_reg8(mem_buf, env->data_bus[248]);
			break;
		case 259:
			return gdb_get_reg8(mem_buf, env->data_bus[249]);
			break;
		case 260:
			return gdb_get_reg8(mem_buf, env->data_bus[250]);
			break;
		case 261:
			return gdb_get_reg8(mem_buf, env->data_bus[251]);
			break;
		case 262:
			return gdb_get_reg8(mem_buf, env->data_bus[252]);
			break;
		case 263:
			return gdb_get_reg8(mem_buf, env->data_bus[253]);
			break;
		case 264:
			return gdb_get_reg8(mem_buf, env->data_bus[254]);
			break;
		case 265:
			return gdb_get_reg8(mem_buf, env->data_bus[255]);
			break;
		case 266:
			return gdb_get_reg8(mem_buf, env->data_bus[256]);
			break;
		case 267:
			return gdb_get_reg8(mem_buf, env->data_bus[257]);
			break;
		case 268:
			return gdb_get_reg8(mem_buf, env->data_bus[258]);
			break;
		case 269:
			return gdb_get_reg8(mem_buf, env->data_bus[259]);
			break;
		case 270:
			return gdb_get_reg8(mem_buf, env->data_bus[260]);
			break;
		case 271:
			return gdb_get_reg8(mem_buf, env->data_bus[261]);
			break;
		case 272:
			return gdb_get_reg8(mem_buf, env->data_bus[262]);
			break;
		case 273:
			return gdb_get_reg8(mem_buf, env->data_bus[263]);
			break;
		case 274:
			return gdb_get_reg8(mem_buf, env->data_bus[264]);
			break;
		case 275:
			return gdb_get_reg8(mem_buf, env->data_bus[265]);
			break;
		case 276:
			return gdb_get_reg8(mem_buf, env->data_bus[266]);
			break;
		case 277:
			return gdb_get_reg8(mem_buf, env->data_bus[267]);
			break;
		case 278:
			return gdb_get_reg8(mem_buf, env->data_bus[268]);
			break;
		case 279:
			return gdb_get_reg8(mem_buf, env->data_bus[269]);
			break;
		case 280:
			return gdb_get_reg8(mem_buf, env->data_bus[270]);
			break;
		case 281:
			return gdb_get_reg8(mem_buf, env->data_bus[271]);
			break;
		case 282:
			return gdb_get_reg8(mem_buf, env->data_bus[272]);
			break;
		case 283:
			return gdb_get_reg8(mem_buf, env->data_bus[273]);
			break;
		case 284:
			return gdb_get_reg8(mem_buf, env->data_bus[274]);
			break;
		case 285:
			return gdb_get_reg8(mem_buf, env->data_bus[275]);
			break;
		case 286:
			return gdb_get_reg8(mem_buf, env->data_bus[276]);
			break;
		case 287:
			return gdb_get_reg8(mem_buf, env->data_bus[277]);
			break;
		case 288:
			return gdb_get_reg8(mem_buf, env->data_bus[278]);
			break;
		case 289:
			return gdb_get_reg8(mem_buf, env->data_bus[279]);
			break;
		case 290:
			return gdb_get_reg8(mem_buf, env->data_bus[280]);
			break;
		case 291:
			return gdb_get_reg8(mem_buf, env->data_bus[281]);
			break;
		case 292:
			return gdb_get_reg8(mem_buf, env->data_bus[282]);
			break;
		case 293:
			return gdb_get_reg8(mem_buf, env->data_bus[283]);
			break;
		case 294:
			return gdb_get_reg8(mem_buf, env->data_bus[284]);
			break;
		case 295:
			return gdb_get_reg8(mem_buf, env->data_bus[285]);
			break;
		case 296:
			return gdb_get_reg8(mem_buf, env->data_bus[286]);
			break;
		case 297:
			return gdb_get_reg8(mem_buf, env->data_bus[287]);
			break;
		case 298:
			return gdb_get_reg8(mem_buf, env->data_bus[288]);
			break;
		case 299:
			return gdb_get_reg8(mem_buf, env->data_bus[289]);
			break;
		case 300:
			return gdb_get_reg8(mem_buf, env->data_bus[290]);
			break;
		case 301:
			return gdb_get_reg8(mem_buf, env->data_bus[291]);
			break;
		case 302:
			return gdb_get_reg8(mem_buf, env->data_bus[292]);
			break;
		case 303:
			return gdb_get_reg8(mem_buf, env->data_bus[293]);
			break;
		case 304:
			return gdb_get_reg8(mem_buf, env->data_bus[294]);
			break;
		case 305:
			return gdb_get_reg8(mem_buf, env->data_bus[295]);
			break;
		case 306:
			return gdb_get_reg8(mem_buf, env->data_bus[296]);
			break;
		case 307:
			return gdb_get_reg8(mem_buf, env->data_bus[297]);
			break;
		case 308:
			return gdb_get_reg8(mem_buf, env->data_bus[298]);
			break;
		case 309:
			return gdb_get_reg8(mem_buf, env->data_bus[299]);
			break;
		case 310:
			return gdb_get_reg8(mem_buf, env->data_bus[300]);
			break;
		case 311:
			return gdb_get_reg8(mem_buf, env->data_bus[301]);
			break;
		case 312:
			return gdb_get_reg8(mem_buf, env->data_bus[302]);
			break;
		case 313:
			return gdb_get_reg8(mem_buf, env->data_bus[303]);
			break;
		case 314:
			return gdb_get_reg8(mem_buf, env->data_bus[304]);
			break;
		case 315:
			return gdb_get_reg8(mem_buf, env->data_bus[305]);
			break;
		case 316:
			return gdb_get_reg8(mem_buf, env->data_bus[306]);
			break;
		case 317:
			return gdb_get_reg8(mem_buf, env->data_bus[307]);
			break;
		case 318:
			return gdb_get_reg8(mem_buf, env->data_bus[308]);
			break;
		case 319:
			return gdb_get_reg8(mem_buf, env->data_bus[309]);
			break;
		case 320:
			return gdb_get_reg8(mem_buf, env->data_bus[310]);
			break;
		case 321:
			return gdb_get_reg8(mem_buf, env->data_bus[311]);
			break;
		case 322:
			return gdb_get_reg8(mem_buf, env->data_bus[312]);
			break;
		case 323:
			return gdb_get_reg8(mem_buf, env->data_bus[313]);
			break;
		case 324:
			return gdb_get_reg8(mem_buf, env->data_bus[314]);
			break;
		case 325:
			return gdb_get_reg8(mem_buf, env->data_bus[315]);
			break;
		case 326:
			return gdb_get_reg8(mem_buf, env->data_bus[316]);
			break;
		case 327:
			return gdb_get_reg8(mem_buf, env->data_bus[317]);
			break;
		case 328:
			return gdb_get_reg8(mem_buf, env->data_bus[318]);
			break;
		case 329:
			return gdb_get_reg8(mem_buf, env->data_bus[319]);
			break;
		case 330:
			return gdb_get_reg8(mem_buf, env->data_bus[320]);
			break;
		case 331:
			return gdb_get_reg8(mem_buf, env->data_bus[321]);
			break;
		case 332:
			return gdb_get_reg8(mem_buf, env->data_bus[322]);
			break;
		case 333:
			return gdb_get_reg8(mem_buf, env->data_bus[323]);
			break;
		case 334:
			return gdb_get_reg8(mem_buf, env->data_bus[324]);
			break;
		case 335:
			return gdb_get_reg8(mem_buf, env->data_bus[325]);
			break;
		case 336:
			return gdb_get_reg8(mem_buf, env->data_bus[326]);
			break;
		case 337:
			return gdb_get_reg8(mem_buf, env->data_bus[327]);
			break;
		case 338:
			return gdb_get_reg8(mem_buf, env->data_bus[328]);
			break;
		case 339:
			return gdb_get_reg8(mem_buf, env->data_bus[329]);
			break;
		case 340:
			return gdb_get_reg8(mem_buf, env->data_bus[330]);
			break;
		case 341:
			return gdb_get_reg8(mem_buf, env->data_bus[331]);
			break;
		case 342:
			return gdb_get_reg8(mem_buf, env->data_bus[332]);
			break;
		case 343:
			return gdb_get_reg8(mem_buf, env->data_bus[333]);
			break;
		case 344:
			return gdb_get_reg8(mem_buf, env->data_bus[334]);
			break;
		case 345:
			return gdb_get_reg8(mem_buf, env->data_bus[335]);
			break;
		case 346:
			return gdb_get_reg8(mem_buf, env->data_bus[336]);
			break;
		case 347:
			return gdb_get_reg8(mem_buf, env->data_bus[337]);
			break;
		case 348:
			return gdb_get_reg8(mem_buf, env->data_bus[338]);
			break;
		case 349:
			return gdb_get_reg8(mem_buf, env->data_bus[339]);
			break;
		case 350:
			return gdb_get_reg8(mem_buf, env->data_bus[340]);
			break;
		case 351:
			return gdb_get_reg8(mem_buf, env->data_bus[341]);
			break;
		case 352:
			return gdb_get_reg8(mem_buf, env->data_bus[342]);
			break;
		case 353:
			return gdb_get_reg8(mem_buf, env->data_bus[343]);
			break;
		case 354:
			return gdb_get_reg8(mem_buf, env->data_bus[344]);
			break;
		case 355:
			return gdb_get_reg8(mem_buf, env->data_bus[345]);
			break;
		case 356:
			return gdb_get_reg8(mem_buf, env->data_bus[346]);
			break;
		case 357:
			return gdb_get_reg8(mem_buf, env->data_bus[347]);
			break;
		case 358:
			return gdb_get_reg8(mem_buf, env->data_bus[348]);
			break;
		case 359:
			return gdb_get_reg8(mem_buf, env->data_bus[349]);
			break;
		case 360:
			return gdb_get_reg8(mem_buf, env->data_bus[350]);
			break;
		case 361:
			return gdb_get_reg8(mem_buf, env->data_bus[351]);
			break;
		case 362:
			return gdb_get_reg8(mem_buf, env->data_bus[352]);
			break;
		case 363:
			return gdb_get_reg8(mem_buf, env->data_bus[353]);
			break;
		case 364:
			return gdb_get_reg8(mem_buf, env->data_bus[354]);
			break;
		case 365:
			return gdb_get_reg8(mem_buf, env->data_bus[355]);
			break;
		case 366:
			return gdb_get_reg8(mem_buf, env->data_bus[356]);
			break;
		case 367:
			return gdb_get_reg8(mem_buf, env->data_bus[357]);
			break;
		case 368:
			return gdb_get_reg8(mem_buf, env->data_bus[358]);
			break;
		case 369:
			return gdb_get_reg8(mem_buf, env->data_bus[359]);
			break;
		case 370:
			return gdb_get_reg8(mem_buf, env->data_bus[360]);
			break;
		case 371:
			return gdb_get_reg8(mem_buf, env->data_bus[361]);
			break;
		case 372:
			return gdb_get_reg8(mem_buf, env->data_bus[362]);
			break;
		case 373:
			return gdb_get_reg8(mem_buf, env->data_bus[363]);
			break;
		case 374:
			return gdb_get_reg8(mem_buf, env->data_bus[364]);
			break;
		case 375:
			return gdb_get_reg8(mem_buf, env->data_bus[365]);
			break;
		case 376:
			return gdb_get_reg8(mem_buf, env->data_bus[366]);
			break;
		case 377:
			return gdb_get_reg8(mem_buf, env->data_bus[367]);
			break;
		case 378:
			return gdb_get_reg8(mem_buf, env->data_bus[368]);
			break;
		case 379:
			return gdb_get_reg8(mem_buf, env->data_bus[369]);
			break;
		case 380:
			return gdb_get_reg8(mem_buf, env->data_bus[370]);
			break;
		case 381:
			return gdb_get_reg8(mem_buf, env->data_bus[371]);
			break;
		case 382:
			return gdb_get_reg8(mem_buf, env->data_bus[372]);
			break;
		case 383:
			return gdb_get_reg8(mem_buf, env->data_bus[373]);
			break;
		case 384:
			return gdb_get_reg8(mem_buf, env->data_bus[374]);
			break;
		case 385:
			return gdb_get_reg8(mem_buf, env->data_bus[375]);
			break;
		case 386:
			return gdb_get_reg8(mem_buf, env->data_bus[376]);
			break;
		case 387:
			return gdb_get_reg8(mem_buf, env->data_bus[377]);
			break;
		case 388:
			return gdb_get_reg8(mem_buf, env->data_bus[378]);
			break;
		case 389:
			return gdb_get_reg8(mem_buf, env->data_bus[379]);
			break;
		case 390:
			return gdb_get_reg8(mem_buf, env->data_bus[380]);
			break;
		case 391:
			return gdb_get_reg8(mem_buf, env->data_bus[381]);
			break;
		case 392:
			return gdb_get_reg8(mem_buf, env->data_bus[382]);
			break;
		case 393:
			return gdb_get_reg8(mem_buf, env->data_bus[383]);
			break;
		case 394:
			return gdb_get_reg8(mem_buf, env->data_bus[384]);
			break;
		case 395:
			return gdb_get_reg8(mem_buf, env->data_bus[385]);
			break;
		case 396:
			return gdb_get_reg8(mem_buf, env->data_bus[386]);
			break;
		case 397:
			return gdb_get_reg8(mem_buf, env->data_bus[387]);
			break;
		case 398:
			return gdb_get_reg8(mem_buf, env->data_bus[388]);
			break;
		case 399:
			return gdb_get_reg8(mem_buf, env->data_bus[389]);
			break;
		case 400:
			return gdb_get_reg8(mem_buf, env->data_bus[390]);
			break;
		case 401:
			return gdb_get_reg8(mem_buf, env->data_bus[391]);
			break;
		case 402:
			return gdb_get_reg8(mem_buf, env->data_bus[392]);
			break;
		case 403:
			return gdb_get_reg8(mem_buf, env->data_bus[393]);
			break;
		case 404:
			return gdb_get_reg8(mem_buf, env->data_bus[394]);
			break;
		case 405:
			return gdb_get_reg8(mem_buf, env->data_bus[395]);
			break;
		case 406:
			return gdb_get_reg8(mem_buf, env->data_bus[396]);
			break;
		case 407:
			return gdb_get_reg8(mem_buf, env->data_bus[397]);
			break;
		case 408:
			return gdb_get_reg8(mem_buf, env->data_bus[398]);
			break;
		case 409:
			return gdb_get_reg8(mem_buf, env->data_bus[399]);
			break;
		case 410:
			return gdb_get_reg8(mem_buf, env->data_bus[400]);
			break;
		case 411:
			return gdb_get_reg8(mem_buf, env->data_bus[401]);
			break;
		case 412:
			return gdb_get_reg8(mem_buf, env->data_bus[402]);
			break;
		case 413:
			return gdb_get_reg8(mem_buf, env->data_bus[403]);
			break;
		case 414:
			return gdb_get_reg8(mem_buf, env->data_bus[404]);
			break;
		case 415:
			return gdb_get_reg8(mem_buf, env->data_bus[405]);
			break;
		case 416:
			return gdb_get_reg8(mem_buf, env->data_bus[406]);
			break;
		case 417:
			return gdb_get_reg8(mem_buf, env->data_bus[407]);
			break;
		case 418:
			return gdb_get_reg8(mem_buf, env->data_bus[408]);
			break;
		case 419:
			return gdb_get_reg8(mem_buf, env->data_bus[409]);
			break;
		case 420:
			return gdb_get_reg8(mem_buf, env->data_bus[410]);
			break;
		case 421:
			return gdb_get_reg8(mem_buf, env->data_bus[411]);
			break;
		case 422:
			return gdb_get_reg8(mem_buf, env->data_bus[412]);
			break;
		case 423:
			return gdb_get_reg8(mem_buf, env->data_bus[413]);
			break;
		case 424:
			return gdb_get_reg8(mem_buf, env->data_bus[414]);
			break;
		case 425:
			return gdb_get_reg8(mem_buf, env->data_bus[415]);
			break;
		case 426:
			return gdb_get_reg8(mem_buf, env->data_bus[416]);
			break;
		case 427:
			return gdb_get_reg8(mem_buf, env->data_bus[417]);
			break;
		case 428:
			return gdb_get_reg8(mem_buf, env->data_bus[418]);
			break;
		case 429:
			return gdb_get_reg8(mem_buf, env->data_bus[419]);
			break;
		case 430:
			return gdb_get_reg8(mem_buf, env->data_bus[420]);
			break;
		case 431:
			return gdb_get_reg8(mem_buf, env->data_bus[421]);
			break;
		case 432:
			return gdb_get_reg8(mem_buf, env->data_bus[422]);
			break;
		case 433:
			return gdb_get_reg8(mem_buf, env->data_bus[423]);
			break;
		case 434:
			return gdb_get_reg8(mem_buf, env->data_bus[424]);
			break;
		case 435:
			return gdb_get_reg8(mem_buf, env->data_bus[425]);
			break;
		case 436:
			return gdb_get_reg8(mem_buf, env->data_bus[426]);
			break;
		case 437:
			return gdb_get_reg8(mem_buf, env->data_bus[427]);
			break;
		case 438:
			return gdb_get_reg8(mem_buf, env->data_bus[428]);
			break;
		case 439:
			return gdb_get_reg8(mem_buf, env->data_bus[429]);
			break;
		case 440:
			return gdb_get_reg8(mem_buf, env->data_bus[430]);
			break;
		case 441:
			return gdb_get_reg8(mem_buf, env->data_bus[431]);
			break;
		case 442:
			return gdb_get_reg8(mem_buf, env->data_bus[432]);
			break;
		case 443:
			return gdb_get_reg8(mem_buf, env->data_bus[433]);
			break;
		case 444:
			return gdb_get_reg8(mem_buf, env->data_bus[434]);
			break;
		case 445:
			return gdb_get_reg8(mem_buf, env->data_bus[435]);
			break;
		case 446:
			return gdb_get_reg8(mem_buf, env->data_bus[436]);
			break;
		case 447:
			return gdb_get_reg8(mem_buf, env->data_bus[437]);
			break;
		case 448:
			return gdb_get_reg8(mem_buf, env->data_bus[438]);
			break;
		case 449:
			return gdb_get_reg8(mem_buf, env->data_bus[439]);
			break;
		case 450:
			return gdb_get_reg8(mem_buf, env->data_bus[440]);
			break;
		case 451:
			return gdb_get_reg8(mem_buf, env->data_bus[441]);
			break;
		case 452:
			return gdb_get_reg8(mem_buf, env->data_bus[442]);
			break;
		case 453:
			return gdb_get_reg8(mem_buf, env->data_bus[443]);
			break;
		case 454:
			return gdb_get_reg8(mem_buf, env->data_bus[444]);
			break;
		case 455:
			return gdb_get_reg8(mem_buf, env->data_bus[445]);
			break;
		case 456:
			return gdb_get_reg8(mem_buf, env->data_bus[446]);
			break;
		case 457:
			return gdb_get_reg8(mem_buf, env->data_bus[447]);
			break;
		case 458:
			return gdb_get_reg8(mem_buf, env->data_bus[448]);
			break;
		case 459:
			return gdb_get_reg8(mem_buf, env->data_bus[449]);
			break;
		case 460:
			return gdb_get_reg8(mem_buf, env->data_bus[450]);
			break;
		case 461:
			return gdb_get_reg8(mem_buf, env->data_bus[451]);
			break;
		case 462:
			return gdb_get_reg8(mem_buf, env->data_bus[452]);
			break;
		case 463:
			return gdb_get_reg8(mem_buf, env->data_bus[453]);
			break;
		case 464:
			return gdb_get_reg8(mem_buf, env->data_bus[454]);
			break;
		case 465:
			return gdb_get_reg8(mem_buf, env->data_bus[455]);
			break;
		case 466:
			return gdb_get_reg8(mem_buf, env->data_bus[456]);
			break;
		case 467:
			return gdb_get_reg8(mem_buf, env->data_bus[457]);
			break;
		case 468:
			return gdb_get_reg8(mem_buf, env->data_bus[458]);
			break;
		case 469:
			return gdb_get_reg8(mem_buf, env->data_bus[459]);
			break;
		case 470:
			return gdb_get_reg8(mem_buf, env->data_bus[460]);
			break;
		case 471:
			return gdb_get_reg8(mem_buf, env->data_bus[461]);
			break;
		case 472:
			return gdb_get_reg8(mem_buf, env->data_bus[462]);
			break;
		case 473:
			return gdb_get_reg8(mem_buf, env->data_bus[463]);
			break;
		case 474:
			return gdb_get_reg8(mem_buf, env->data_bus[464]);
			break;
		case 475:
			return gdb_get_reg8(mem_buf, env->data_bus[465]);
			break;
		case 476:
			return gdb_get_reg8(mem_buf, env->data_bus[466]);
			break;
		case 477:
			return gdb_get_reg8(mem_buf, env->data_bus[467]);
			break;
		case 478:
			return gdb_get_reg8(mem_buf, env->data_bus[468]);
			break;
		case 479:
			return gdb_get_reg8(mem_buf, env->data_bus[469]);
			break;
		case 480:
			return gdb_get_reg8(mem_buf, env->data_bus[470]);
			break;
		case 481:
			return gdb_get_reg8(mem_buf, env->data_bus[471]);
			break;
		case 482:
			return gdb_get_reg8(mem_buf, env->data_bus[472]);
			break;
		case 483:
			return gdb_get_reg8(mem_buf, env->data_bus[473]);
			break;
		case 484:
			return gdb_get_reg8(mem_buf, env->data_bus[474]);
			break;
		case 485:
			return gdb_get_reg8(mem_buf, env->data_bus[475]);
			break;
		case 486:
			return gdb_get_reg8(mem_buf, env->data_bus[476]);
			break;
		case 487:
			return gdb_get_reg8(mem_buf, env->data_bus[477]);
			break;
		case 488:
			return gdb_get_reg8(mem_buf, env->data_bus[478]);
			break;
		case 489:
			return gdb_get_reg8(mem_buf, env->data_bus[479]);
			break;
		case 490:
			return gdb_get_reg8(mem_buf, env->data_bus[480]);
			break;
		case 491:
			return gdb_get_reg8(mem_buf, env->data_bus[481]);
			break;
		case 492:
			return gdb_get_reg8(mem_buf, env->data_bus[482]);
			break;
		case 493:
			return gdb_get_reg8(mem_buf, env->data_bus[483]);
			break;
		case 494:
			return gdb_get_reg8(mem_buf, env->data_bus[484]);
			break;
		case 495:
			return gdb_get_reg8(mem_buf, env->data_bus[485]);
			break;
		case 496:
			return gdb_get_reg8(mem_buf, env->data_bus[486]);
			break;
		case 497:
			return gdb_get_reg8(mem_buf, env->data_bus[487]);
			break;
		case 498:
			return gdb_get_reg8(mem_buf, env->data_bus[488]);
			break;
		case 499:
			return gdb_get_reg8(mem_buf, env->data_bus[489]);
			break;
		case 500:
			return gdb_get_reg8(mem_buf, env->data_bus[490]);
			break;
		case 501:
			return gdb_get_reg8(mem_buf, env->data_bus[491]);
			break;
		case 502:
			return gdb_get_reg8(mem_buf, env->data_bus[492]);
			break;
		case 503:
			return gdb_get_reg8(mem_buf, env->data_bus[493]);
			break;
		case 504:
			return gdb_get_reg8(mem_buf, env->data_bus[494]);
			break;
		case 505:
			return gdb_get_reg8(mem_buf, env->data_bus[495]);
			break;
		case 506:
			return gdb_get_reg8(mem_buf, env->data_bus[496]);
			break;
		case 507:
			return gdb_get_reg8(mem_buf, env->data_bus[497]);
			break;
		case 508:
			return gdb_get_reg8(mem_buf, env->data_bus[498]);
			break;
		case 509:
			return gdb_get_reg8(mem_buf, env->data_bus[499]);
			break;
		case 510:
			return gdb_get_reg8(mem_buf, env->data_bus[500]);
			break;
		case 511:
			return gdb_get_reg8(mem_buf, env->data_bus[501]);
			break;
		case 512:
			return gdb_get_reg8(mem_buf, env->data_bus[502]);
			break;
		case 513:
			return gdb_get_reg8(mem_buf, env->data_bus[503]);
			break;
		case 514:
			return gdb_get_reg8(mem_buf, env->data_bus[504]);
			break;
		case 515:
			return gdb_get_reg8(mem_buf, env->data_bus[505]);
			break;
		case 516:
			return gdb_get_reg8(mem_buf, env->data_bus[506]);
			break;
		case 517:
			return gdb_get_reg8(mem_buf, env->data_bus[507]);
			break;
		case 518:
			return gdb_get_reg8(mem_buf, env->data_bus[508]);
			break;
		case 519:
			return gdb_get_reg8(mem_buf, env->data_bus[509]);
			break;
		case 520:
			return gdb_get_reg8(mem_buf, env->data_bus[510]);
			break;
		case 521:
			return gdb_get_reg8(mem_buf, env->data_bus[511]);
			break;
		case 522:
			return gdb_get_reg8(mem_buf, env->data_bus[512]);
			break;
		case 523:
			return gdb_get_reg8(mem_buf, env->data_bus[513]);
			break;
		case 524:
			return gdb_get_reg8(mem_buf, env->data_bus[514]);
			break;
		case 525:
			return gdb_get_reg8(mem_buf, env->data_bus[515]);
			break;
		case 526:
			return gdb_get_reg8(mem_buf, env->data_bus[516]);
			break;
		case 527:
			return gdb_get_reg8(mem_buf, env->data_bus[517]);
			break;
		case 528:
			return gdb_get_reg8(mem_buf, env->data_bus[518]);
			break;
		case 529:
			return gdb_get_reg8(mem_buf, env->data_bus[519]);
			break;
		case 530:
			return gdb_get_reg8(mem_buf, env->data_bus[520]);
			break;
		case 531:
			return gdb_get_reg8(mem_buf, env->data_bus[521]);
			break;
		case 532:
			return gdb_get_reg8(mem_buf, env->data_bus[522]);
			break;
		case 533:
			return gdb_get_reg8(mem_buf, env->data_bus[523]);
			break;
		case 534:
			return gdb_get_reg8(mem_buf, env->data_bus[524]);
			break;
		case 535:
			return gdb_get_reg8(mem_buf, env->data_bus[525]);
			break;
		case 536:
			return gdb_get_reg8(mem_buf, env->data_bus[526]);
			break;
		case 537:
			return gdb_get_reg8(mem_buf, env->data_bus[527]);
			break;
		case 538:
			return gdb_get_reg8(mem_buf, env->data_bus[528]);
			break;
		case 539:
			return gdb_get_reg8(mem_buf, env->data_bus[529]);
			break;
		case 540:
			return gdb_get_reg8(mem_buf, env->data_bus[530]);
			break;
		case 541:
			return gdb_get_reg8(mem_buf, env->data_bus[531]);
			break;
		case 542:
			return gdb_get_reg8(mem_buf, env->data_bus[532]);
			break;
		case 543:
			return gdb_get_reg8(mem_buf, env->data_bus[533]);
			break;
		case 544:
			return gdb_get_reg8(mem_buf, env->data_bus[534]);
			break;
		case 545:
			return gdb_get_reg8(mem_buf, env->data_bus[535]);
			break;
		case 546:
			return gdb_get_reg8(mem_buf, env->data_bus[536]);
			break;
		case 547:
			return gdb_get_reg8(mem_buf, env->data_bus[537]);
			break;
		case 548:
			return gdb_get_reg8(mem_buf, env->data_bus[538]);
			break;
		case 549:
			return gdb_get_reg8(mem_buf, env->data_bus[539]);
			break;
		case 550:
			return gdb_get_reg8(mem_buf, env->data_bus[540]);
			break;
		case 551:
			return gdb_get_reg8(mem_buf, env->data_bus[541]);
			break;
		case 552:
			return gdb_get_reg8(mem_buf, env->data_bus[542]);
			break;
		case 553:
			return gdb_get_reg8(mem_buf, env->data_bus[543]);
			break;
		case 554:
			return gdb_get_reg8(mem_buf, env->data_bus[544]);
			break;
		case 555:
			return gdb_get_reg8(mem_buf, env->data_bus[545]);
			break;
		case 556:
			return gdb_get_reg8(mem_buf, env->data_bus[546]);
			break;
		case 557:
			return gdb_get_reg8(mem_buf, env->data_bus[547]);
			break;
		case 558:
			return gdb_get_reg8(mem_buf, env->data_bus[548]);
			break;
		case 559:
			return gdb_get_reg8(mem_buf, env->data_bus[549]);
			break;
		case 560:
			return gdb_get_reg8(mem_buf, env->data_bus[550]);
			break;
		case 561:
			return gdb_get_reg8(mem_buf, env->data_bus[551]);
			break;
		case 562:
			return gdb_get_reg8(mem_buf, env->data_bus[552]);
			break;
		case 563:
			return gdb_get_reg8(mem_buf, env->data_bus[553]);
			break;
		case 564:
			return gdb_get_reg8(mem_buf, env->data_bus[554]);
			break;
		case 565:
			return gdb_get_reg8(mem_buf, env->data_bus[555]);
			break;
		case 566:
			return gdb_get_reg8(mem_buf, env->data_bus[556]);
			break;
		case 567:
			return gdb_get_reg8(mem_buf, env->data_bus[557]);
			break;
		case 568:
			return gdb_get_reg8(mem_buf, env->data_bus[558]);
			break;
		case 569:
			return gdb_get_reg8(mem_buf, env->data_bus[559]);
			break;
		case 570:
			return gdb_get_reg8(mem_buf, env->data_bus[560]);
			break;
		case 571:
			return gdb_get_reg8(mem_buf, env->data_bus[561]);
			break;
		case 572:
			return gdb_get_reg8(mem_buf, env->data_bus[562]);
			break;
		case 573:
			return gdb_get_reg8(mem_buf, env->data_bus[563]);
			break;
		case 574:
			return gdb_get_reg8(mem_buf, env->data_bus[564]);
			break;
		case 575:
			return gdb_get_reg8(mem_buf, env->data_bus[565]);
			break;
		case 576:
			return gdb_get_reg8(mem_buf, env->data_bus[566]);
			break;
		case 577:
			return gdb_get_reg8(mem_buf, env->data_bus[567]);
			break;
		case 578:
			return gdb_get_reg8(mem_buf, env->data_bus[568]);
			break;
		case 579:
			return gdb_get_reg8(mem_buf, env->data_bus[569]);
			break;
		case 580:
			return gdb_get_reg8(mem_buf, env->data_bus[570]);
			break;
		case 581:
			return gdb_get_reg8(mem_buf, env->data_bus[571]);
			break;
		case 582:
			return gdb_get_reg8(mem_buf, env->data_bus[572]);
			break;
		case 583:
			return gdb_get_reg8(mem_buf, env->data_bus[573]);
			break;
		case 584:
			return gdb_get_reg8(mem_buf, env->data_bus[574]);
			break;
		case 585:
			return gdb_get_reg8(mem_buf, env->data_bus[575]);
			break;
		case 586:
			return gdb_get_reg8(mem_buf, env->data_bus[576]);
			break;
		case 587:
			return gdb_get_reg8(mem_buf, env->data_bus[577]);
			break;
		case 588:
			return gdb_get_reg8(mem_buf, env->data_bus[578]);
			break;
		case 589:
			return gdb_get_reg8(mem_buf, env->data_bus[579]);
			break;
		case 590:
			return gdb_get_reg8(mem_buf, env->data_bus[580]);
			break;
		case 591:
			return gdb_get_reg8(mem_buf, env->data_bus[581]);
			break;
		case 592:
			return gdb_get_reg8(mem_buf, env->data_bus[582]);
			break;
		case 593:
			return gdb_get_reg8(mem_buf, env->data_bus[583]);
			break;
		case 594:
			return gdb_get_reg8(mem_buf, env->data_bus[584]);
			break;
		case 595:
			return gdb_get_reg8(mem_buf, env->data_bus[585]);
			break;
		case 596:
			return gdb_get_reg8(mem_buf, env->data_bus[586]);
			break;
		case 597:
			return gdb_get_reg8(mem_buf, env->data_bus[587]);
			break;
		case 598:
			return gdb_get_reg8(mem_buf, env->data_bus[588]);
			break;
		case 599:
			return gdb_get_reg8(mem_buf, env->data_bus[589]);
			break;
		case 600:
			return gdb_get_reg8(mem_buf, env->data_bus[590]);
			break;
		case 601:
			return gdb_get_reg8(mem_buf, env->data_bus[591]);
			break;
		case 602:
			return gdb_get_reg8(mem_buf, env->data_bus[592]);
			break;
		case 603:
			return gdb_get_reg8(mem_buf, env->data_bus[593]);
			break;
		case 604:
			return gdb_get_reg8(mem_buf, env->data_bus[594]);
			break;
		case 605:
			return gdb_get_reg8(mem_buf, env->data_bus[595]);
			break;
		case 606:
			return gdb_get_reg8(mem_buf, env->data_bus[596]);
			break;
		case 607:
			return gdb_get_reg8(mem_buf, env->data_bus[597]);
			break;
		case 608:
			return gdb_get_reg8(mem_buf, env->data_bus[598]);
			break;
		case 609:
			return gdb_get_reg8(mem_buf, env->data_bus[599]);
			break;
		case 610:
			return gdb_get_reg8(mem_buf, env->data_bus[600]);
			break;
		case 611:
			return gdb_get_reg8(mem_buf, env->data_bus[601]);
			break;
		case 612:
			return gdb_get_reg8(mem_buf, env->data_bus[602]);
			break;
		case 613:
			return gdb_get_reg8(mem_buf, env->data_bus[603]);
			break;
		case 614:
			return gdb_get_reg8(mem_buf, env->data_bus[604]);
			break;
		case 615:
			return gdb_get_reg8(mem_buf, env->data_bus[605]);
			break;
		case 616:
			return gdb_get_reg8(mem_buf, env->data_bus[606]);
			break;
		case 617:
			return gdb_get_reg8(mem_buf, env->data_bus[607]);
			break;
		case 618:
			return gdb_get_reg8(mem_buf, env->data_bus[608]);
			break;
		case 619:
			return gdb_get_reg8(mem_buf, env->data_bus[609]);
			break;
		case 620:
			return gdb_get_reg8(mem_buf, env->data_bus[610]);
			break;
		case 621:
			return gdb_get_reg8(mem_buf, env->data_bus[611]);
			break;
		case 622:
			return gdb_get_reg8(mem_buf, env->data_bus[612]);
			break;
		case 623:
			return gdb_get_reg8(mem_buf, env->data_bus[613]);
			break;
		case 624:
			return gdb_get_reg8(mem_buf, env->data_bus[614]);
			break;
		case 625:
			return gdb_get_reg8(mem_buf, env->data_bus[615]);
			break;
		case 626:
			return gdb_get_reg8(mem_buf, env->data_bus[616]);
			break;
		case 627:
			return gdb_get_reg8(mem_buf, env->data_bus[617]);
			break;
		case 628:
			return gdb_get_reg8(mem_buf, env->data_bus[618]);
			break;
		case 629:
			return gdb_get_reg8(mem_buf, env->data_bus[619]);
			break;
		case 630:
			return gdb_get_reg8(mem_buf, env->data_bus[620]);
			break;
		case 631:
			return gdb_get_reg8(mem_buf, env->data_bus[621]);
			break;
		case 632:
			return gdb_get_reg8(mem_buf, env->data_bus[622]);
			break;
		case 633:
			return gdb_get_reg8(mem_buf, env->data_bus[623]);
			break;
		case 634:
			return gdb_get_reg8(mem_buf, env->data_bus[624]);
			break;
		case 635:
			return gdb_get_reg8(mem_buf, env->data_bus[625]);
			break;
		case 636:
			return gdb_get_reg8(mem_buf, env->data_bus[626]);
			break;
		case 637:
			return gdb_get_reg8(mem_buf, env->data_bus[627]);
			break;
		case 638:
			return gdb_get_reg8(mem_buf, env->data_bus[628]);
			break;
		case 639:
			return gdb_get_reg8(mem_buf, env->data_bus[629]);
			break;
		case 640:
			return gdb_get_reg8(mem_buf, env->data_bus[630]);
			break;
		case 641:
			return gdb_get_reg8(mem_buf, env->data_bus[631]);
			break;
		case 642:
			return gdb_get_reg8(mem_buf, env->data_bus[632]);
			break;
		case 643:
			return gdb_get_reg8(mem_buf, env->data_bus[633]);
			break;
		case 644:
			return gdb_get_reg8(mem_buf, env->data_bus[634]);
			break;
		case 645:
			return gdb_get_reg8(mem_buf, env->data_bus[635]);
			break;
		case 646:
			return gdb_get_reg8(mem_buf, env->data_bus[636]);
			break;
		case 647:
			return gdb_get_reg8(mem_buf, env->data_bus[637]);
			break;
		case 648:
			return gdb_get_reg8(mem_buf, env->data_bus[638]);
			break;
		case 649:
			return gdb_get_reg8(mem_buf, env->data_bus[639]);
			break;
		case 650:
			return gdb_get_reg8(mem_buf, env->data_bus[640]);
			break;
		case 651:
			return gdb_get_reg8(mem_buf, env->data_bus[641]);
			break;
		case 652:
			return gdb_get_reg8(mem_buf, env->data_bus[642]);
			break;
		case 653:
			return gdb_get_reg8(mem_buf, env->data_bus[643]);
			break;
		case 654:
			return gdb_get_reg8(mem_buf, env->data_bus[644]);
			break;
		case 655:
			return gdb_get_reg8(mem_buf, env->data_bus[645]);
			break;
		case 656:
			return gdb_get_reg8(mem_buf, env->data_bus[646]);
			break;
		case 657:
			return gdb_get_reg8(mem_buf, env->data_bus[647]);
			break;
		case 658:
			return gdb_get_reg8(mem_buf, env->data_bus[648]);
			break;
		case 659:
			return gdb_get_reg8(mem_buf, env->data_bus[649]);
			break;
		case 660:
			return gdb_get_reg8(mem_buf, env->data_bus[650]);
			break;
		case 661:
			return gdb_get_reg8(mem_buf, env->data_bus[651]);
			break;
		case 662:
			return gdb_get_reg8(mem_buf, env->data_bus[652]);
			break;
		case 663:
			return gdb_get_reg8(mem_buf, env->data_bus[653]);
			break;
		case 664:
			return gdb_get_reg8(mem_buf, env->data_bus[654]);
			break;
		case 665:
			return gdb_get_reg8(mem_buf, env->data_bus[655]);
			break;
		case 666:
			return gdb_get_reg8(mem_buf, env->data_bus[656]);
			break;
		case 667:
			return gdb_get_reg8(mem_buf, env->data_bus[657]);
			break;
		case 668:
			return gdb_get_reg8(mem_buf, env->data_bus[658]);
			break;
		case 669:
			return gdb_get_reg8(mem_buf, env->data_bus[659]);
			break;
		case 670:
			return gdb_get_reg8(mem_buf, env->data_bus[660]);
			break;
		case 671:
			return gdb_get_reg8(mem_buf, env->data_bus[661]);
			break;
		case 672:
			return gdb_get_reg8(mem_buf, env->data_bus[662]);
			break;
		case 673:
			return gdb_get_reg8(mem_buf, env->data_bus[663]);
			break;
		case 674:
			return gdb_get_reg8(mem_buf, env->data_bus[664]);
			break;
		case 675:
			return gdb_get_reg8(mem_buf, env->data_bus[665]);
			break;
		case 676:
			return gdb_get_reg8(mem_buf, env->data_bus[666]);
			break;
		case 677:
			return gdb_get_reg8(mem_buf, env->data_bus[667]);
			break;
		case 678:
			return gdb_get_reg8(mem_buf, env->data_bus[668]);
			break;
		case 679:
			return gdb_get_reg8(mem_buf, env->data_bus[669]);
			break;
		case 680:
			return gdb_get_reg8(mem_buf, env->data_bus[670]);
			break;
		case 681:
			return gdb_get_reg8(mem_buf, env->data_bus[671]);
			break;
		case 682:
			return gdb_get_reg8(mem_buf, env->data_bus[672]);
			break;
		case 683:
			return gdb_get_reg8(mem_buf, env->data_bus[673]);
			break;
		case 684:
			return gdb_get_reg8(mem_buf, env->data_bus[674]);
			break;
		case 685:
			return gdb_get_reg8(mem_buf, env->data_bus[675]);
			break;
		case 686:
			return gdb_get_reg8(mem_buf, env->data_bus[676]);
			break;
		case 687:
			return gdb_get_reg8(mem_buf, env->data_bus[677]);
			break;
		case 688:
			return gdb_get_reg8(mem_buf, env->data_bus[678]);
			break;
		case 689:
			return gdb_get_reg8(mem_buf, env->data_bus[679]);
			break;
		case 690:
			return gdb_get_reg8(mem_buf, env->data_bus[680]);
			break;
		case 691:
			return gdb_get_reg8(mem_buf, env->data_bus[681]);
			break;
		case 692:
			return gdb_get_reg8(mem_buf, env->data_bus[682]);
			break;
		case 693:
			return gdb_get_reg8(mem_buf, env->data_bus[683]);
			break;
		case 694:
			return gdb_get_reg8(mem_buf, env->data_bus[684]);
			break;
		case 695:
			return gdb_get_reg8(mem_buf, env->data_bus[685]);
			break;
		case 696:
			return gdb_get_reg8(mem_buf, env->data_bus[686]);
			break;
		case 697:
			return gdb_get_reg8(mem_buf, env->data_bus[687]);
			break;
		case 698:
			return gdb_get_reg8(mem_buf, env->data_bus[688]);
			break;
		case 699:
			return gdb_get_reg8(mem_buf, env->data_bus[689]);
			break;
		case 700:
			return gdb_get_reg8(mem_buf, env->data_bus[690]);
			break;
		case 701:
			return gdb_get_reg8(mem_buf, env->data_bus[691]);
			break;
		case 702:
			return gdb_get_reg8(mem_buf, env->data_bus[692]);
			break;
		case 703:
			return gdb_get_reg8(mem_buf, env->data_bus[693]);
			break;
		case 704:
			return gdb_get_reg8(mem_buf, env->data_bus[694]);
			break;
		case 705:
			return gdb_get_reg8(mem_buf, env->data_bus[695]);
			break;
		case 706:
			return gdb_get_reg8(mem_buf, env->data_bus[696]);
			break;
		case 707:
			return gdb_get_reg8(mem_buf, env->data_bus[697]);
			break;
		case 708:
			return gdb_get_reg8(mem_buf, env->data_bus[698]);
			break;
		case 709:
			return gdb_get_reg8(mem_buf, env->data_bus[699]);
			break;
		case 710:
			return gdb_get_reg8(mem_buf, env->data_bus[700]);
			break;
		case 711:
			return gdb_get_reg8(mem_buf, env->data_bus[701]);
			break;
		case 712:
			return gdb_get_reg8(mem_buf, env->data_bus[702]);
			break;
		case 713:
			return gdb_get_reg8(mem_buf, env->data_bus[703]);
			break;
		case 714:
			return gdb_get_reg8(mem_buf, env->data_bus[704]);
			break;
		case 715:
			return gdb_get_reg8(mem_buf, env->data_bus[705]);
			break;
		case 716:
			return gdb_get_reg8(mem_buf, env->data_bus[706]);
			break;
		case 717:
			return gdb_get_reg8(mem_buf, env->data_bus[707]);
			break;
		case 718:
			return gdb_get_reg8(mem_buf, env->data_bus[708]);
			break;
		case 719:
			return gdb_get_reg8(mem_buf, env->data_bus[709]);
			break;
		case 720:
			return gdb_get_reg8(mem_buf, env->data_bus[710]);
			break;
		case 721:
			return gdb_get_reg8(mem_buf, env->data_bus[711]);
			break;
		case 722:
			return gdb_get_reg8(mem_buf, env->data_bus[712]);
			break;
		case 723:
			return gdb_get_reg8(mem_buf, env->data_bus[713]);
			break;
		case 724:
			return gdb_get_reg8(mem_buf, env->data_bus[714]);
			break;
		case 725:
			return gdb_get_reg8(mem_buf, env->data_bus[715]);
			break;
		case 726:
			return gdb_get_reg8(mem_buf, env->data_bus[716]);
			break;
		case 727:
			return gdb_get_reg8(mem_buf, env->data_bus[717]);
			break;
		case 728:
			return gdb_get_reg8(mem_buf, env->data_bus[718]);
			break;
		case 729:
			return gdb_get_reg8(mem_buf, env->data_bus[719]);
			break;
		case 730:
			return gdb_get_reg8(mem_buf, env->data_bus[720]);
			break;
		case 731:
			return gdb_get_reg8(mem_buf, env->data_bus[721]);
			break;
		case 732:
			return gdb_get_reg8(mem_buf, env->data_bus[722]);
			break;
		case 733:
			return gdb_get_reg8(mem_buf, env->data_bus[723]);
			break;
		case 734:
			return gdb_get_reg8(mem_buf, env->data_bus[724]);
			break;
		case 735:
			return gdb_get_reg8(mem_buf, env->data_bus[725]);
			break;
		case 736:
			return gdb_get_reg8(mem_buf, env->data_bus[726]);
			break;
		case 737:
			return gdb_get_reg8(mem_buf, env->data_bus[727]);
			break;
		case 738:
			return gdb_get_reg8(mem_buf, env->data_bus[728]);
			break;
		case 739:
			return gdb_get_reg8(mem_buf, env->data_bus[729]);
			break;
		case 740:
			return gdb_get_reg8(mem_buf, env->data_bus[730]);
			break;
		case 741:
			return gdb_get_reg8(mem_buf, env->data_bus[731]);
			break;
		case 742:
			return gdb_get_reg8(mem_buf, env->data_bus[732]);
			break;
		case 743:
			return gdb_get_reg8(mem_buf, env->data_bus[733]);
			break;
		case 744:
			return gdb_get_reg8(mem_buf, env->data_bus[734]);
			break;
		case 745:
			return gdb_get_reg8(mem_buf, env->data_bus[735]);
			break;
		case 746:
			return gdb_get_reg8(mem_buf, env->data_bus[736]);
			break;
		case 747:
			return gdb_get_reg8(mem_buf, env->data_bus[737]);
			break;
		case 748:
			return gdb_get_reg8(mem_buf, env->data_bus[738]);
			break;
		case 749:
			return gdb_get_reg8(mem_buf, env->data_bus[739]);
			break;
		case 750:
			return gdb_get_reg8(mem_buf, env->data_bus[740]);
			break;
		case 751:
			return gdb_get_reg8(mem_buf, env->data_bus[741]);
			break;
		case 752:
			return gdb_get_reg8(mem_buf, env->data_bus[742]);
			break;
		case 753:
			return gdb_get_reg8(mem_buf, env->data_bus[743]);
			break;
		case 754:
			return gdb_get_reg8(mem_buf, env->data_bus[744]);
			break;
		case 755:
			return gdb_get_reg8(mem_buf, env->data_bus[745]);
			break;
		case 756:
			return gdb_get_reg8(mem_buf, env->data_bus[746]);
			break;
		case 757:
			return gdb_get_reg8(mem_buf, env->data_bus[747]);
			break;
		case 758:
			return gdb_get_reg8(mem_buf, env->data_bus[748]);
			break;
		case 759:
			return gdb_get_reg8(mem_buf, env->data_bus[749]);
			break;
		case 760:
			return gdb_get_reg8(mem_buf, env->data_bus[750]);
			break;
		case 761:
			return gdb_get_reg8(mem_buf, env->data_bus[751]);
			break;
		case 762:
			return gdb_get_reg8(mem_buf, env->data_bus[752]);
			break;
		case 763:
			return gdb_get_reg8(mem_buf, env->data_bus[753]);
			break;
		case 764:
			return gdb_get_reg8(mem_buf, env->data_bus[754]);
			break;
		case 765:
			return gdb_get_reg8(mem_buf, env->data_bus[755]);
			break;
		case 766:
			return gdb_get_reg8(mem_buf, env->data_bus[756]);
			break;
		case 767:
			return gdb_get_reg8(mem_buf, env->data_bus[757]);
			break;
		case 768:
			return gdb_get_reg8(mem_buf, env->data_bus[758]);
			break;
		case 769:
			return gdb_get_reg8(mem_buf, env->data_bus[759]);
			break;
		case 770:
			return gdb_get_reg8(mem_buf, env->data_bus[760]);
			break;
		case 771:
			return gdb_get_reg8(mem_buf, env->data_bus[761]);
			break;
		case 772:
			return gdb_get_reg8(mem_buf, env->data_bus[762]);
			break;
		case 773:
			return gdb_get_reg8(mem_buf, env->data_bus[763]);
			break;
		case 774:
			return gdb_get_reg8(mem_buf, env->data_bus[764]);
			break;
		case 775:
			return gdb_get_reg8(mem_buf, env->data_bus[765]);
			break;
		case 776:
			return gdb_get_reg8(mem_buf, env->data_bus[766]);
			break;
		case 777:
			return gdb_get_reg8(mem_buf, env->data_bus[767]);
			break;
		case 778:
			return gdb_get_reg8(mem_buf, env->data_bus[768]);
			break;
		case 779:
			return gdb_get_reg8(mem_buf, env->data_bus[769]);
			break;
		case 780:
			return gdb_get_reg8(mem_buf, env->data_bus[770]);
			break;
		case 781:
			return gdb_get_reg8(mem_buf, env->data_bus[771]);
			break;
		case 782:
			return gdb_get_reg8(mem_buf, env->data_bus[772]);
			break;
		case 783:
			return gdb_get_reg8(mem_buf, env->data_bus[773]);
			break;
		case 784:
			return gdb_get_reg8(mem_buf, env->data_bus[774]);
			break;
		case 785:
			return gdb_get_reg8(mem_buf, env->data_bus[775]);
			break;
		case 786:
			return gdb_get_reg8(mem_buf, env->data_bus[776]);
			break;
		case 787:
			return gdb_get_reg8(mem_buf, env->data_bus[777]);
			break;
		case 788:
			return gdb_get_reg8(mem_buf, env->data_bus[778]);
			break;
		case 789:
			return gdb_get_reg8(mem_buf, env->data_bus[779]);
			break;
		case 790:
			return gdb_get_reg8(mem_buf, env->data_bus[780]);
			break;
		case 791:
			return gdb_get_reg8(mem_buf, env->data_bus[781]);
			break;
		case 792:
			return gdb_get_reg8(mem_buf, env->data_bus[782]);
			break;
		case 793:
			return gdb_get_reg8(mem_buf, env->data_bus[783]);
			break;
		case 794:
			return gdb_get_reg8(mem_buf, env->data_bus[784]);
			break;
		case 795:
			return gdb_get_reg8(mem_buf, env->data_bus[785]);
			break;
		case 796:
			return gdb_get_reg8(mem_buf, env->data_bus[786]);
			break;
		case 797:
			return gdb_get_reg8(mem_buf, env->data_bus[787]);
			break;
		case 798:
			return gdb_get_reg8(mem_buf, env->data_bus[788]);
			break;
		case 799:
			return gdb_get_reg8(mem_buf, env->data_bus[789]);
			break;
		case 800:
			return gdb_get_reg8(mem_buf, env->data_bus[790]);
			break;
		case 801:
			return gdb_get_reg8(mem_buf, env->data_bus[791]);
			break;
		case 802:
			return gdb_get_reg8(mem_buf, env->data_bus[792]);
			break;
		case 803:
			return gdb_get_reg8(mem_buf, env->data_bus[793]);
			break;
		case 804:
			return gdb_get_reg8(mem_buf, env->data_bus[794]);
			break;
		case 805:
			return gdb_get_reg8(mem_buf, env->data_bus[795]);
			break;
		case 806:
			return gdb_get_reg8(mem_buf, env->data_bus[796]);
			break;
		case 807:
			return gdb_get_reg8(mem_buf, env->data_bus[797]);
			break;
		case 808:
			return gdb_get_reg8(mem_buf, env->data_bus[798]);
			break;
		case 809:
			return gdb_get_reg8(mem_buf, env->data_bus[799]);
			break;
		case 810:
			return gdb_get_reg8(mem_buf, env->data_bus[800]);
			break;
		case 811:
			return gdb_get_reg8(mem_buf, env->data_bus[801]);
			break;
		case 812:
			return gdb_get_reg8(mem_buf, env->data_bus[802]);
			break;
		case 813:
			return gdb_get_reg8(mem_buf, env->data_bus[803]);
			break;
		case 814:
			return gdb_get_reg8(mem_buf, env->data_bus[804]);
			break;
		case 815:
			return gdb_get_reg8(mem_buf, env->data_bus[805]);
			break;
		case 816:
			return gdb_get_reg8(mem_buf, env->data_bus[806]);
			break;
		case 817:
			return gdb_get_reg8(mem_buf, env->data_bus[807]);
			break;
		case 818:
			return gdb_get_reg8(mem_buf, env->data_bus[808]);
			break;
		case 819:
			return gdb_get_reg8(mem_buf, env->data_bus[809]);
			break;
		case 820:
			return gdb_get_reg8(mem_buf, env->data_bus[810]);
			break;
		case 821:
			return gdb_get_reg8(mem_buf, env->data_bus[811]);
			break;
		case 822:
			return gdb_get_reg8(mem_buf, env->data_bus[812]);
			break;
		case 823:
			return gdb_get_reg8(mem_buf, env->data_bus[813]);
			break;
		case 824:
			return gdb_get_reg8(mem_buf, env->data_bus[814]);
			break;
		case 825:
			return gdb_get_reg8(mem_buf, env->data_bus[815]);
			break;
		case 826:
			return gdb_get_reg8(mem_buf, env->data_bus[816]);
			break;
		case 827:
			return gdb_get_reg8(mem_buf, env->data_bus[817]);
			break;
		case 828:
			return gdb_get_reg8(mem_buf, env->data_bus[818]);
			break;
		case 829:
			return gdb_get_reg8(mem_buf, env->data_bus[819]);
			break;
		case 830:
			return gdb_get_reg8(mem_buf, env->data_bus[820]);
			break;
		case 831:
			return gdb_get_reg8(mem_buf, env->data_bus[821]);
			break;
		case 832:
			return gdb_get_reg8(mem_buf, env->data_bus[822]);
			break;
		case 833:
			return gdb_get_reg8(mem_buf, env->data_bus[823]);
			break;
		case 834:
			return gdb_get_reg8(mem_buf, env->data_bus[824]);
			break;
		case 835:
			return gdb_get_reg8(mem_buf, env->data_bus[825]);
			break;
		case 836:
			return gdb_get_reg8(mem_buf, env->data_bus[826]);
			break;
		case 837:
			return gdb_get_reg8(mem_buf, env->data_bus[827]);
			break;
		case 838:
			return gdb_get_reg8(mem_buf, env->data_bus[828]);
			break;
		case 839:
			return gdb_get_reg8(mem_buf, env->data_bus[829]);
			break;
		case 840:
			return gdb_get_reg8(mem_buf, env->data_bus[830]);
			break;
		case 841:
			return gdb_get_reg8(mem_buf, env->data_bus[831]);
			break;
		case 842:
			return gdb_get_reg8(mem_buf, env->data_bus[832]);
			break;
		case 843:
			return gdb_get_reg8(mem_buf, env->data_bus[833]);
			break;
		case 844:
			return gdb_get_reg8(mem_buf, env->data_bus[834]);
			break;
		case 845:
			return gdb_get_reg8(mem_buf, env->data_bus[835]);
			break;
		case 846:
			return gdb_get_reg8(mem_buf, env->data_bus[836]);
			break;
		case 847:
			return gdb_get_reg8(mem_buf, env->data_bus[837]);
			break;
		case 848:
			return gdb_get_reg8(mem_buf, env->data_bus[838]);
			break;
		case 849:
			return gdb_get_reg8(mem_buf, env->data_bus[839]);
			break;
		case 850:
			return gdb_get_reg8(mem_buf, env->data_bus[840]);
			break;
		case 851:
			return gdb_get_reg8(mem_buf, env->data_bus[841]);
			break;
		case 852:
			return gdb_get_reg8(mem_buf, env->data_bus[842]);
			break;
		case 853:
			return gdb_get_reg8(mem_buf, env->data_bus[843]);
			break;
		case 854:
			return gdb_get_reg8(mem_buf, env->data_bus[844]);
			break;
		case 855:
			return gdb_get_reg8(mem_buf, env->data_bus[845]);
			break;
		case 856:
			return gdb_get_reg8(mem_buf, env->data_bus[846]);
			break;
		case 857:
			return gdb_get_reg8(mem_buf, env->data_bus[847]);
			break;
		case 858:
			return gdb_get_reg8(mem_buf, env->data_bus[848]);
			break;
		case 859:
			return gdb_get_reg8(mem_buf, env->data_bus[849]);
			break;
		case 860:
			return gdb_get_reg8(mem_buf, env->data_bus[850]);
			break;
		case 861:
			return gdb_get_reg8(mem_buf, env->data_bus[851]);
			break;
		case 862:
			return gdb_get_reg8(mem_buf, env->data_bus[852]);
			break;
		case 863:
			return gdb_get_reg8(mem_buf, env->data_bus[853]);
			break;
		case 864:
			return gdb_get_reg8(mem_buf, env->data_bus[854]);
			break;
		case 865:
			return gdb_get_reg8(mem_buf, env->data_bus[855]);
			break;
		case 866:
			return gdb_get_reg8(mem_buf, env->data_bus[856]);
			break;
		case 867:
			return gdb_get_reg8(mem_buf, env->data_bus[857]);
			break;
		case 868:
			return gdb_get_reg8(mem_buf, env->data_bus[858]);
			break;
		case 869:
			return gdb_get_reg8(mem_buf, env->data_bus[859]);
			break;
		case 870:
			return gdb_get_reg8(mem_buf, env->data_bus[860]);
			break;
		case 871:
			return gdb_get_reg8(mem_buf, env->data_bus[861]);
			break;
		case 872:
			return gdb_get_reg8(mem_buf, env->data_bus[862]);
			break;
		case 873:
			return gdb_get_reg8(mem_buf, env->data_bus[863]);
			break;
		case 874:
			return gdb_get_reg8(mem_buf, env->data_bus[864]);
			break;
		case 875:
			return gdb_get_reg8(mem_buf, env->data_bus[865]);
			break;
		case 876:
			return gdb_get_reg8(mem_buf, env->data_bus[866]);
			break;
		case 877:
			return gdb_get_reg8(mem_buf, env->data_bus[867]);
			break;
		case 878:
			return gdb_get_reg8(mem_buf, env->data_bus[868]);
			break;
		case 879:
			return gdb_get_reg8(mem_buf, env->data_bus[869]);
			break;
		case 880:
			return gdb_get_reg8(mem_buf, env->data_bus[870]);
			break;
		case 881:
			return gdb_get_reg8(mem_buf, env->data_bus[871]);
			break;
		case 882:
			return gdb_get_reg8(mem_buf, env->data_bus[872]);
			break;
		case 883:
			return gdb_get_reg8(mem_buf, env->data_bus[873]);
			break;
		case 884:
			return gdb_get_reg8(mem_buf, env->data_bus[874]);
			break;
		case 885:
			return gdb_get_reg8(mem_buf, env->data_bus[875]);
			break;
		case 886:
			return gdb_get_reg8(mem_buf, env->data_bus[876]);
			break;
		case 887:
			return gdb_get_reg8(mem_buf, env->data_bus[877]);
			break;
		case 888:
			return gdb_get_reg8(mem_buf, env->data_bus[878]);
			break;
		case 889:
			return gdb_get_reg8(mem_buf, env->data_bus[879]);
			break;
		case 890:
			return gdb_get_reg8(mem_buf, env->data_bus[880]);
			break;
		case 891:
			return gdb_get_reg8(mem_buf, env->data_bus[881]);
			break;
		case 892:
			return gdb_get_reg8(mem_buf, env->data_bus[882]);
			break;
		case 893:
			return gdb_get_reg8(mem_buf, env->data_bus[883]);
			break;
		case 894:
			return gdb_get_reg8(mem_buf, env->data_bus[884]);
			break;
		case 895:
			return gdb_get_reg8(mem_buf, env->data_bus[885]);
			break;
		case 896:
			return gdb_get_reg8(mem_buf, env->data_bus[886]);
			break;
		case 897:
			return gdb_get_reg8(mem_buf, env->data_bus[887]);
			break;
		case 898:
			return gdb_get_reg8(mem_buf, env->data_bus[888]);
			break;
		case 899:
			return gdb_get_reg8(mem_buf, env->data_bus[889]);
			break;
		case 900:
			return gdb_get_reg8(mem_buf, env->data_bus[890]);
			break;
		case 901:
			return gdb_get_reg8(mem_buf, env->data_bus[891]);
			break;
		case 902:
			return gdb_get_reg8(mem_buf, env->data_bus[892]);
			break;
		case 903:
			return gdb_get_reg8(mem_buf, env->data_bus[893]);
			break;
		case 904:
			return gdb_get_reg8(mem_buf, env->data_bus[894]);
			break;
		case 905:
			return gdb_get_reg8(mem_buf, env->data_bus[895]);
			break;
		case 906:
			return gdb_get_reg8(mem_buf, env->data_bus[896]);
			break;
		case 907:
			return gdb_get_reg8(mem_buf, env->data_bus[897]);
			break;
		case 908:
			return gdb_get_reg8(mem_buf, env->data_bus[898]);
			break;
		case 909:
			return gdb_get_reg8(mem_buf, env->data_bus[899]);
			break;
		case 910:
			return gdb_get_reg8(mem_buf, env->data_bus[900]);
			break;
		case 911:
			return gdb_get_reg8(mem_buf, env->data_bus[901]);
			break;
		case 912:
			return gdb_get_reg8(mem_buf, env->data_bus[902]);
			break;
		case 913:
			return gdb_get_reg8(mem_buf, env->data_bus[903]);
			break;
		case 914:
			return gdb_get_reg8(mem_buf, env->data_bus[904]);
			break;
		case 915:
			return gdb_get_reg8(mem_buf, env->data_bus[905]);
			break;
		case 916:
			return gdb_get_reg8(mem_buf, env->data_bus[906]);
			break;
		case 917:
			return gdb_get_reg8(mem_buf, env->data_bus[907]);
			break;
		case 918:
			return gdb_get_reg8(mem_buf, env->data_bus[908]);
			break;
		case 919:
			return gdb_get_reg8(mem_buf, env->data_bus[909]);
			break;
		case 920:
			return gdb_get_reg8(mem_buf, env->data_bus[910]);
			break;
		case 921:
			return gdb_get_reg8(mem_buf, env->data_bus[911]);
			break;
		case 922:
			return gdb_get_reg8(mem_buf, env->data_bus[912]);
			break;
		case 923:
			return gdb_get_reg8(mem_buf, env->data_bus[913]);
			break;
		case 924:
			return gdb_get_reg8(mem_buf, env->data_bus[914]);
			break;
		case 925:
			return gdb_get_reg8(mem_buf, env->data_bus[915]);
			break;
		case 926:
			return gdb_get_reg8(mem_buf, env->data_bus[916]);
			break;
		case 927:
			return gdb_get_reg8(mem_buf, env->data_bus[917]);
			break;
		case 928:
			return gdb_get_reg8(mem_buf, env->data_bus[918]);
			break;
		case 929:
			return gdb_get_reg8(mem_buf, env->data_bus[919]);
			break;
		case 930:
			return gdb_get_reg8(mem_buf, env->data_bus[920]);
			break;
		case 931:
			return gdb_get_reg8(mem_buf, env->data_bus[921]);
			break;
		case 932:
			return gdb_get_reg8(mem_buf, env->data_bus[922]);
			break;
		case 933:
			return gdb_get_reg8(mem_buf, env->data_bus[923]);
			break;
		case 934:
			return gdb_get_reg8(mem_buf, env->data_bus[924]);
			break;
		case 935:
			return gdb_get_reg8(mem_buf, env->data_bus[925]);
			break;
		case 936:
			return gdb_get_reg8(mem_buf, env->data_bus[926]);
			break;
		case 937:
			return gdb_get_reg8(mem_buf, env->data_bus[927]);
			break;
		case 938:
			return gdb_get_reg8(mem_buf, env->data_bus[928]);
			break;
		case 939:
			return gdb_get_reg8(mem_buf, env->data_bus[929]);
			break;
		case 940:
			return gdb_get_reg8(mem_buf, env->data_bus[930]);
			break;
		case 941:
			return gdb_get_reg8(mem_buf, env->data_bus[931]);
			break;
		case 942:
			return gdb_get_reg8(mem_buf, env->data_bus[932]);
			break;
		case 943:
			return gdb_get_reg8(mem_buf, env->data_bus[933]);
			break;
		case 944:
			return gdb_get_reg8(mem_buf, env->data_bus[934]);
			break;
		case 945:
			return gdb_get_reg8(mem_buf, env->data_bus[935]);
			break;
		case 946:
			return gdb_get_reg8(mem_buf, env->data_bus[936]);
			break;
		case 947:
			return gdb_get_reg8(mem_buf, env->data_bus[937]);
			break;
		case 948:
			return gdb_get_reg8(mem_buf, env->data_bus[938]);
			break;
		case 949:
			return gdb_get_reg8(mem_buf, env->data_bus[939]);
			break;
		case 950:
			return gdb_get_reg8(mem_buf, env->data_bus[940]);
			break;
		case 951:
			return gdb_get_reg8(mem_buf, env->data_bus[941]);
			break;
		case 952:
			return gdb_get_reg8(mem_buf, env->data_bus[942]);
			break;
		case 953:
			return gdb_get_reg8(mem_buf, env->data_bus[943]);
			break;
		case 954:
			return gdb_get_reg8(mem_buf, env->data_bus[944]);
			break;
		case 955:
			return gdb_get_reg8(mem_buf, env->data_bus[945]);
			break;
		case 956:
			return gdb_get_reg8(mem_buf, env->data_bus[946]);
			break;
		case 957:
			return gdb_get_reg8(mem_buf, env->data_bus[947]);
			break;
		case 958:
			return gdb_get_reg8(mem_buf, env->data_bus[948]);
			break;
		case 959:
			return gdb_get_reg8(mem_buf, env->data_bus[949]);
			break;
		case 960:
			return gdb_get_reg8(mem_buf, env->data_bus[950]);
			break;
		case 961:
			return gdb_get_reg8(mem_buf, env->data_bus[951]);
			break;
		case 962:
			return gdb_get_reg8(mem_buf, env->data_bus[952]);
			break;
		case 963:
			return gdb_get_reg8(mem_buf, env->data_bus[953]);
			break;
		case 964:
			return gdb_get_reg8(mem_buf, env->data_bus[954]);
			break;
		case 965:
			return gdb_get_reg8(mem_buf, env->data_bus[955]);
			break;
		case 966:
			return gdb_get_reg8(mem_buf, env->data_bus[956]);
			break;
		case 967:
			return gdb_get_reg8(mem_buf, env->data_bus[957]);
			break;
		case 968:
			return gdb_get_reg8(mem_buf, env->data_bus[958]);
			break;
		case 969:
			return gdb_get_reg8(mem_buf, env->data_bus[959]);
			break;
		case 970:
			return gdb_get_reg8(mem_buf, env->data_bus[960]);
			break;
		case 971:
			return gdb_get_reg8(mem_buf, env->data_bus[961]);
			break;
		case 972:
			return gdb_get_reg8(mem_buf, env->data_bus[962]);
			break;
		case 973:
			return gdb_get_reg8(mem_buf, env->data_bus[963]);
			break;
		case 974:
			return gdb_get_reg8(mem_buf, env->data_bus[964]);
			break;
		case 975:
			return gdb_get_reg8(mem_buf, env->data_bus[965]);
			break;
		case 976:
			return gdb_get_reg8(mem_buf, env->data_bus[966]);
			break;
		case 977:
			return gdb_get_reg8(mem_buf, env->data_bus[967]);
			break;
		case 978:
			return gdb_get_reg8(mem_buf, env->data_bus[968]);
			break;
		case 979:
			return gdb_get_reg8(mem_buf, env->data_bus[969]);
			break;
		case 980:
			return gdb_get_reg8(mem_buf, env->data_bus[970]);
			break;
		case 981:
			return gdb_get_reg8(mem_buf, env->data_bus[971]);
			break;
		case 982:
			return gdb_get_reg8(mem_buf, env->data_bus[972]);
			break;
		case 983:
			return gdb_get_reg8(mem_buf, env->data_bus[973]);
			break;
		case 984:
			return gdb_get_reg8(mem_buf, env->data_bus[974]);
			break;
		case 985:
			return gdb_get_reg8(mem_buf, env->data_bus[975]);
			break;
		case 986:
			return gdb_get_reg8(mem_buf, env->data_bus[976]);
			break;
		case 987:
			return gdb_get_reg8(mem_buf, env->data_bus[977]);
			break;
		case 988:
			return gdb_get_reg8(mem_buf, env->data_bus[978]);
			break;
		case 989:
			return gdb_get_reg8(mem_buf, env->data_bus[979]);
			break;
		case 990:
			return gdb_get_reg8(mem_buf, env->data_bus[980]);
			break;
		case 991:
			return gdb_get_reg8(mem_buf, env->data_bus[981]);
			break;
		case 992:
			return gdb_get_reg8(mem_buf, env->data_bus[982]);
			break;
		case 993:
			return gdb_get_reg8(mem_buf, env->data_bus[983]);
			break;
		case 994:
			return gdb_get_reg8(mem_buf, env->data_bus[984]);
			break;
		case 995:
			return gdb_get_reg8(mem_buf, env->data_bus[985]);
			break;
		case 996:
			return gdb_get_reg8(mem_buf, env->data_bus[986]);
			break;
		case 997:
			return gdb_get_reg8(mem_buf, env->data_bus[987]);
			break;
		case 998:
			return gdb_get_reg8(mem_buf, env->data_bus[988]);
			break;
		case 999:
			return gdb_get_reg8(mem_buf, env->data_bus[989]);
			break;
		case 1000:
			return gdb_get_reg8(mem_buf, env->data_bus[990]);
			break;
		case 1001:
			return gdb_get_reg8(mem_buf, env->data_bus[991]);
			break;
		case 1002:
			return gdb_get_reg8(mem_buf, env->data_bus[992]);
			break;
		case 1003:
			return gdb_get_reg8(mem_buf, env->data_bus[993]);
			break;
		case 1004:
			return gdb_get_reg8(mem_buf, env->data_bus[994]);
			break;
		case 1005:
			return gdb_get_reg8(mem_buf, env->data_bus[995]);
			break;
		case 1006:
			return gdb_get_reg8(mem_buf, env->data_bus[996]);
			break;
		case 1007:
			return gdb_get_reg8(mem_buf, env->data_bus[997]);
			break;
		case 1008:
			return gdb_get_reg8(mem_buf, env->data_bus[998]);
			break;
		case 1009:
			return gdb_get_reg8(mem_buf, env->data_bus[999]);
			break;
		case 1010:
			return gdb_get_reg8(mem_buf, env->data_bus[1000]);
			break;
		case 1011:
			return gdb_get_reg8(mem_buf, env->data_bus[1001]);
			break;
		case 1012:
			return gdb_get_reg8(mem_buf, env->data_bus[1002]);
			break;
		case 1013:
			return gdb_get_reg8(mem_buf, env->data_bus[1003]);
			break;
		case 1014:
			return gdb_get_reg8(mem_buf, env->data_bus[1004]);
			break;
		case 1015:
			return gdb_get_reg8(mem_buf, env->data_bus[1005]);
			break;
		case 1016:
			return gdb_get_reg8(mem_buf, env->data_bus[1006]);
			break;
		case 1017:
			return gdb_get_reg8(mem_buf, env->data_bus[1007]);
			break;
		case 1018:
			return gdb_get_reg8(mem_buf, env->data_bus[1008]);
			break;
		case 1019:
			return gdb_get_reg8(mem_buf, env->data_bus[1009]);
			break;
		case 1020:
			return gdb_get_reg8(mem_buf, env->data_bus[1010]);
			break;
		case 1021:
			return gdb_get_reg8(mem_buf, env->data_bus[1011]);
			break;
		case 1022:
			return gdb_get_reg8(mem_buf, env->data_bus[1012]);
			break;
		case 1023:
			return gdb_get_reg8(mem_buf, env->data_bus[1013]);
			break;
		case 1024:
			return gdb_get_reg8(mem_buf, env->data_bus[1014]);
			break;
		case 1025:
			return gdb_get_reg8(mem_buf, env->data_bus[1015]);
			break;
		case 1026:
			return gdb_get_reg8(mem_buf, env->data_bus[1016]);
			break;
		case 1027:
			return gdb_get_reg8(mem_buf, env->data_bus[1017]);
			break;
		case 1028:
			return gdb_get_reg8(mem_buf, env->data_bus[1018]);
			break;
		case 1029:
			return gdb_get_reg8(mem_buf, env->data_bus[1019]);
			break;
		case 1030:
			return gdb_get_reg8(mem_buf, env->data_bus[1020]);
			break;
		case 1031:
			return gdb_get_reg8(mem_buf, env->data_bus[1021]);
			break;
		case 1032:
			return gdb_get_reg8(mem_buf, env->data_bus[1022]);
			break;
		case 1033:
			return gdb_get_reg8(mem_buf, env->data_bus[1023]);
			break;
		case 1034:
			return gdb_get_reg64(mem_buf, env->CoinBase);
			break;
		case 1035:
			return gdb_get_reg64(mem_buf, env->TimeStamp);
			break;
		case 1036:
			return gdb_get_reg64(mem_buf, env->Number);
			break;
		case 1037:
			return gdb_get_reg64(mem_buf, env->Difficulty);
			break;
		case 1038:
			return gdb_get_reg64(mem_buf, env->GasLimit);
			break;
		default:
			return 0;
	}
}

int ppdl_cpu_gdb_write_register(CPUState *cs, uint8_t *mem_buf, int reg) {
	PPDLCPU *cpu = PPDL_CPU(cs);
	CPUClass *cc = CPU_GET_CLASS(cs);
	CPUPPDLState *env = &cpu->env;
	uint32_t tmp;
	if (reg > cc->gdb_num_core_regs) {
		/*
		 * Unknown register
		 */
		return 0;
	}
	tmp = ldl_p(mem_buf);
	switch (reg) {
		case 0:
			env->pc = tmp;
			return 4;
			break;
		case 1:
			env->cur_addr = tmp;
			return 8;
			break;
		case 2:
			env->caller_addr = tmp;
			return 8;
			break;
		case 3:
			env->origin_addr = tmp;
			return 8;
			break;
		case 4:
			env->gas_price = tmp;
			return 4;
			break;
		case 5:
			env->ext_code_size = tmp;
			return 8;
			break;
		case 6:
			env->inp_data_size = tmp;
			return 8;
			break;
		case 7:
			env->log_ptr = tmp;
			return 4;
			break;
		case 8:
			env->sp = tmp;
			return 4;
			break;
		case 9:
			env->gas_available = tmp;
			return 4;
			break;
		case 10:
			env->data_bus[0] = tmp;
			return 1;
			break;
		case 11:
			env->data_bus[1] = tmp;
			return 1;
			break;
		case 12:
			env->data_bus[2] = tmp;
			return 1;
			break;
		case 13:
			env->data_bus[3] = tmp;
			return 1;
			break;
		case 14:
			env->data_bus[4] = tmp;
			return 1;
			break;
		case 15:
			env->data_bus[5] = tmp;
			return 1;
			break;
		case 16:
			env->data_bus[6] = tmp;
			return 1;
			break;
		case 17:
			env->data_bus[7] = tmp;
			return 1;
			break;
		case 18:
			env->data_bus[8] = tmp;
			return 1;
			break;
		case 19:
			env->data_bus[9] = tmp;
			return 1;
			break;
		case 20:
			env->data_bus[10] = tmp;
			return 1;
			break;
		case 21:
			env->data_bus[11] = tmp;
			return 1;
			break;
		case 22:
			env->data_bus[12] = tmp;
			return 1;
			break;
		case 23:
			env->data_bus[13] = tmp;
			return 1;
			break;
		case 24:
			env->data_bus[14] = tmp;
			return 1;
			break;
		case 25:
			env->data_bus[15] = tmp;
			return 1;
			break;
		case 26:
			env->data_bus[16] = tmp;
			return 1;
			break;
		case 27:
			env->data_bus[17] = tmp;
			return 1;
			break;
		case 28:
			env->data_bus[18] = tmp;
			return 1;
			break;
		case 29:
			env->data_bus[19] = tmp;
			return 1;
			break;
		case 30:
			env->data_bus[20] = tmp;
			return 1;
			break;
		case 31:
			env->data_bus[21] = tmp;
			return 1;
			break;
		case 32:
			env->data_bus[22] = tmp;
			return 1;
			break;
		case 33:
			env->data_bus[23] = tmp;
			return 1;
			break;
		case 34:
			env->data_bus[24] = tmp;
			return 1;
			break;
		case 35:
			env->data_bus[25] = tmp;
			return 1;
			break;
		case 36:
			env->data_bus[26] = tmp;
			return 1;
			break;
		case 37:
			env->data_bus[27] = tmp;
			return 1;
			break;
		case 38:
			env->data_bus[28] = tmp;
			return 1;
			break;
		case 39:
			env->data_bus[29] = tmp;
			return 1;
			break;
		case 40:
			env->data_bus[30] = tmp;
			return 1;
			break;
		case 41:
			env->data_bus[31] = tmp;
			return 1;
			break;
		case 42:
			env->data_bus[32] = tmp;
			return 1;
			break;
		case 43:
			env->data_bus[33] = tmp;
			return 1;
			break;
		case 44:
			env->data_bus[34] = tmp;
			return 1;
			break;
		case 45:
			env->data_bus[35] = tmp;
			return 1;
			break;
		case 46:
			env->data_bus[36] = tmp;
			return 1;
			break;
		case 47:
			env->data_bus[37] = tmp;
			return 1;
			break;
		case 48:
			env->data_bus[38] = tmp;
			return 1;
			break;
		case 49:
			env->data_bus[39] = tmp;
			return 1;
			break;
		case 50:
			env->data_bus[40] = tmp;
			return 1;
			break;
		case 51:
			env->data_bus[41] = tmp;
			return 1;
			break;
		case 52:
			env->data_bus[42] = tmp;
			return 1;
			break;
		case 53:
			env->data_bus[43] = tmp;
			return 1;
			break;
		case 54:
			env->data_bus[44] = tmp;
			return 1;
			break;
		case 55:
			env->data_bus[45] = tmp;
			return 1;
			break;
		case 56:
			env->data_bus[46] = tmp;
			return 1;
			break;
		case 57:
			env->data_bus[47] = tmp;
			return 1;
			break;
		case 58:
			env->data_bus[48] = tmp;
			return 1;
			break;
		case 59:
			env->data_bus[49] = tmp;
			return 1;
			break;
		case 60:
			env->data_bus[50] = tmp;
			return 1;
			break;
		case 61:
			env->data_bus[51] = tmp;
			return 1;
			break;
		case 62:
			env->data_bus[52] = tmp;
			return 1;
			break;
		case 63:
			env->data_bus[53] = tmp;
			return 1;
			break;
		case 64:
			env->data_bus[54] = tmp;
			return 1;
			break;
		case 65:
			env->data_bus[55] = tmp;
			return 1;
			break;
		case 66:
			env->data_bus[56] = tmp;
			return 1;
			break;
		case 67:
			env->data_bus[57] = tmp;
			return 1;
			break;
		case 68:
			env->data_bus[58] = tmp;
			return 1;
			break;
		case 69:
			env->data_bus[59] = tmp;
			return 1;
			break;
		case 70:
			env->data_bus[60] = tmp;
			return 1;
			break;
		case 71:
			env->data_bus[61] = tmp;
			return 1;
			break;
		case 72:
			env->data_bus[62] = tmp;
			return 1;
			break;
		case 73:
			env->data_bus[63] = tmp;
			return 1;
			break;
		case 74:
			env->data_bus[64] = tmp;
			return 1;
			break;
		case 75:
			env->data_bus[65] = tmp;
			return 1;
			break;
		case 76:
			env->data_bus[66] = tmp;
			return 1;
			break;
		case 77:
			env->data_bus[67] = tmp;
			return 1;
			break;
		case 78:
			env->data_bus[68] = tmp;
			return 1;
			break;
		case 79:
			env->data_bus[69] = tmp;
			return 1;
			break;
		case 80:
			env->data_bus[70] = tmp;
			return 1;
			break;
		case 81:
			env->data_bus[71] = tmp;
			return 1;
			break;
		case 82:
			env->data_bus[72] = tmp;
			return 1;
			break;
		case 83:
			env->data_bus[73] = tmp;
			return 1;
			break;
		case 84:
			env->data_bus[74] = tmp;
			return 1;
			break;
		case 85:
			env->data_bus[75] = tmp;
			return 1;
			break;
		case 86:
			env->data_bus[76] = tmp;
			return 1;
			break;
		case 87:
			env->data_bus[77] = tmp;
			return 1;
			break;
		case 88:
			env->data_bus[78] = tmp;
			return 1;
			break;
		case 89:
			env->data_bus[79] = tmp;
			return 1;
			break;
		case 90:
			env->data_bus[80] = tmp;
			return 1;
			break;
		case 91:
			env->data_bus[81] = tmp;
			return 1;
			break;
		case 92:
			env->data_bus[82] = tmp;
			return 1;
			break;
		case 93:
			env->data_bus[83] = tmp;
			return 1;
			break;
		case 94:
			env->data_bus[84] = tmp;
			return 1;
			break;
		case 95:
			env->data_bus[85] = tmp;
			return 1;
			break;
		case 96:
			env->data_bus[86] = tmp;
			return 1;
			break;
		case 97:
			env->data_bus[87] = tmp;
			return 1;
			break;
		case 98:
			env->data_bus[88] = tmp;
			return 1;
			break;
		case 99:
			env->data_bus[89] = tmp;
			return 1;
			break;
		case 100:
			env->data_bus[90] = tmp;
			return 1;
			break;
		case 101:
			env->data_bus[91] = tmp;
			return 1;
			break;
		case 102:
			env->data_bus[92] = tmp;
			return 1;
			break;
		case 103:
			env->data_bus[93] = tmp;
			return 1;
			break;
		case 104:
			env->data_bus[94] = tmp;
			return 1;
			break;
		case 105:
			env->data_bus[95] = tmp;
			return 1;
			break;
		case 106:
			env->data_bus[96] = tmp;
			return 1;
			break;
		case 107:
			env->data_bus[97] = tmp;
			return 1;
			break;
		case 108:
			env->data_bus[98] = tmp;
			return 1;
			break;
		case 109:
			env->data_bus[99] = tmp;
			return 1;
			break;
		case 110:
			env->data_bus[100] = tmp;
			return 1;
			break;
		case 111:
			env->data_bus[101] = tmp;
			return 1;
			break;
		case 112:
			env->data_bus[102] = tmp;
			return 1;
			break;
		case 113:
			env->data_bus[103] = tmp;
			return 1;
			break;
		case 114:
			env->data_bus[104] = tmp;
			return 1;
			break;
		case 115:
			env->data_bus[105] = tmp;
			return 1;
			break;
		case 116:
			env->data_bus[106] = tmp;
			return 1;
			break;
		case 117:
			env->data_bus[107] = tmp;
			return 1;
			break;
		case 118:
			env->data_bus[108] = tmp;
			return 1;
			break;
		case 119:
			env->data_bus[109] = tmp;
			return 1;
			break;
		case 120:
			env->data_bus[110] = tmp;
			return 1;
			break;
		case 121:
			env->data_bus[111] = tmp;
			return 1;
			break;
		case 122:
			env->data_bus[112] = tmp;
			return 1;
			break;
		case 123:
			env->data_bus[113] = tmp;
			return 1;
			break;
		case 124:
			env->data_bus[114] = tmp;
			return 1;
			break;
		case 125:
			env->data_bus[115] = tmp;
			return 1;
			break;
		case 126:
			env->data_bus[116] = tmp;
			return 1;
			break;
		case 127:
			env->data_bus[117] = tmp;
			return 1;
			break;
		case 128:
			env->data_bus[118] = tmp;
			return 1;
			break;
		case 129:
			env->data_bus[119] = tmp;
			return 1;
			break;
		case 130:
			env->data_bus[120] = tmp;
			return 1;
			break;
		case 131:
			env->data_bus[121] = tmp;
			return 1;
			break;
		case 132:
			env->data_bus[122] = tmp;
			return 1;
			break;
		case 133:
			env->data_bus[123] = tmp;
			return 1;
			break;
		case 134:
			env->data_bus[124] = tmp;
			return 1;
			break;
		case 135:
			env->data_bus[125] = tmp;
			return 1;
			break;
		case 136:
			env->data_bus[126] = tmp;
			return 1;
			break;
		case 137:
			env->data_bus[127] = tmp;
			return 1;
			break;
		case 138:
			env->data_bus[128] = tmp;
			return 1;
			break;
		case 139:
			env->data_bus[129] = tmp;
			return 1;
			break;
		case 140:
			env->data_bus[130] = tmp;
			return 1;
			break;
		case 141:
			env->data_bus[131] = tmp;
			return 1;
			break;
		case 142:
			env->data_bus[132] = tmp;
			return 1;
			break;
		case 143:
			env->data_bus[133] = tmp;
			return 1;
			break;
		case 144:
			env->data_bus[134] = tmp;
			return 1;
			break;
		case 145:
			env->data_bus[135] = tmp;
			return 1;
			break;
		case 146:
			env->data_bus[136] = tmp;
			return 1;
			break;
		case 147:
			env->data_bus[137] = tmp;
			return 1;
			break;
		case 148:
			env->data_bus[138] = tmp;
			return 1;
			break;
		case 149:
			env->data_bus[139] = tmp;
			return 1;
			break;
		case 150:
			env->data_bus[140] = tmp;
			return 1;
			break;
		case 151:
			env->data_bus[141] = tmp;
			return 1;
			break;
		case 152:
			env->data_bus[142] = tmp;
			return 1;
			break;
		case 153:
			env->data_bus[143] = tmp;
			return 1;
			break;
		case 154:
			env->data_bus[144] = tmp;
			return 1;
			break;
		case 155:
			env->data_bus[145] = tmp;
			return 1;
			break;
		case 156:
			env->data_bus[146] = tmp;
			return 1;
			break;
		case 157:
			env->data_bus[147] = tmp;
			return 1;
			break;
		case 158:
			env->data_bus[148] = tmp;
			return 1;
			break;
		case 159:
			env->data_bus[149] = tmp;
			return 1;
			break;
		case 160:
			env->data_bus[150] = tmp;
			return 1;
			break;
		case 161:
			env->data_bus[151] = tmp;
			return 1;
			break;
		case 162:
			env->data_bus[152] = tmp;
			return 1;
			break;
		case 163:
			env->data_bus[153] = tmp;
			return 1;
			break;
		case 164:
			env->data_bus[154] = tmp;
			return 1;
			break;
		case 165:
			env->data_bus[155] = tmp;
			return 1;
			break;
		case 166:
			env->data_bus[156] = tmp;
			return 1;
			break;
		case 167:
			env->data_bus[157] = tmp;
			return 1;
			break;
		case 168:
			env->data_bus[158] = tmp;
			return 1;
			break;
		case 169:
			env->data_bus[159] = tmp;
			return 1;
			break;
		case 170:
			env->data_bus[160] = tmp;
			return 1;
			break;
		case 171:
			env->data_bus[161] = tmp;
			return 1;
			break;
		case 172:
			env->data_bus[162] = tmp;
			return 1;
			break;
		case 173:
			env->data_bus[163] = tmp;
			return 1;
			break;
		case 174:
			env->data_bus[164] = tmp;
			return 1;
			break;
		case 175:
			env->data_bus[165] = tmp;
			return 1;
			break;
		case 176:
			env->data_bus[166] = tmp;
			return 1;
			break;
		case 177:
			env->data_bus[167] = tmp;
			return 1;
			break;
		case 178:
			env->data_bus[168] = tmp;
			return 1;
			break;
		case 179:
			env->data_bus[169] = tmp;
			return 1;
			break;
		case 180:
			env->data_bus[170] = tmp;
			return 1;
			break;
		case 181:
			env->data_bus[171] = tmp;
			return 1;
			break;
		case 182:
			env->data_bus[172] = tmp;
			return 1;
			break;
		case 183:
			env->data_bus[173] = tmp;
			return 1;
			break;
		case 184:
			env->data_bus[174] = tmp;
			return 1;
			break;
		case 185:
			env->data_bus[175] = tmp;
			return 1;
			break;
		case 186:
			env->data_bus[176] = tmp;
			return 1;
			break;
		case 187:
			env->data_bus[177] = tmp;
			return 1;
			break;
		case 188:
			env->data_bus[178] = tmp;
			return 1;
			break;
		case 189:
			env->data_bus[179] = tmp;
			return 1;
			break;
		case 190:
			env->data_bus[180] = tmp;
			return 1;
			break;
		case 191:
			env->data_bus[181] = tmp;
			return 1;
			break;
		case 192:
			env->data_bus[182] = tmp;
			return 1;
			break;
		case 193:
			env->data_bus[183] = tmp;
			return 1;
			break;
		case 194:
			env->data_bus[184] = tmp;
			return 1;
			break;
		case 195:
			env->data_bus[185] = tmp;
			return 1;
			break;
		case 196:
			env->data_bus[186] = tmp;
			return 1;
			break;
		case 197:
			env->data_bus[187] = tmp;
			return 1;
			break;
		case 198:
			env->data_bus[188] = tmp;
			return 1;
			break;
		case 199:
			env->data_bus[189] = tmp;
			return 1;
			break;
		case 200:
			env->data_bus[190] = tmp;
			return 1;
			break;
		case 201:
			env->data_bus[191] = tmp;
			return 1;
			break;
		case 202:
			env->data_bus[192] = tmp;
			return 1;
			break;
		case 203:
			env->data_bus[193] = tmp;
			return 1;
			break;
		case 204:
			env->data_bus[194] = tmp;
			return 1;
			break;
		case 205:
			env->data_bus[195] = tmp;
			return 1;
			break;
		case 206:
			env->data_bus[196] = tmp;
			return 1;
			break;
		case 207:
			env->data_bus[197] = tmp;
			return 1;
			break;
		case 208:
			env->data_bus[198] = tmp;
			return 1;
			break;
		case 209:
			env->data_bus[199] = tmp;
			return 1;
			break;
		case 210:
			env->data_bus[200] = tmp;
			return 1;
			break;
		case 211:
			env->data_bus[201] = tmp;
			return 1;
			break;
		case 212:
			env->data_bus[202] = tmp;
			return 1;
			break;
		case 213:
			env->data_bus[203] = tmp;
			return 1;
			break;
		case 214:
			env->data_bus[204] = tmp;
			return 1;
			break;
		case 215:
			env->data_bus[205] = tmp;
			return 1;
			break;
		case 216:
			env->data_bus[206] = tmp;
			return 1;
			break;
		case 217:
			env->data_bus[207] = tmp;
			return 1;
			break;
		case 218:
			env->data_bus[208] = tmp;
			return 1;
			break;
		case 219:
			env->data_bus[209] = tmp;
			return 1;
			break;
		case 220:
			env->data_bus[210] = tmp;
			return 1;
			break;
		case 221:
			env->data_bus[211] = tmp;
			return 1;
			break;
		case 222:
			env->data_bus[212] = tmp;
			return 1;
			break;
		case 223:
			env->data_bus[213] = tmp;
			return 1;
			break;
		case 224:
			env->data_bus[214] = tmp;
			return 1;
			break;
		case 225:
			env->data_bus[215] = tmp;
			return 1;
			break;
		case 226:
			env->data_bus[216] = tmp;
			return 1;
			break;
		case 227:
			env->data_bus[217] = tmp;
			return 1;
			break;
		case 228:
			env->data_bus[218] = tmp;
			return 1;
			break;
		case 229:
			env->data_bus[219] = tmp;
			return 1;
			break;
		case 230:
			env->data_bus[220] = tmp;
			return 1;
			break;
		case 231:
			env->data_bus[221] = tmp;
			return 1;
			break;
		case 232:
			env->data_bus[222] = tmp;
			return 1;
			break;
		case 233:
			env->data_bus[223] = tmp;
			return 1;
			break;
		case 234:
			env->data_bus[224] = tmp;
			return 1;
			break;
		case 235:
			env->data_bus[225] = tmp;
			return 1;
			break;
		case 236:
			env->data_bus[226] = tmp;
			return 1;
			break;
		case 237:
			env->data_bus[227] = tmp;
			return 1;
			break;
		case 238:
			env->data_bus[228] = tmp;
			return 1;
			break;
		case 239:
			env->data_bus[229] = tmp;
			return 1;
			break;
		case 240:
			env->data_bus[230] = tmp;
			return 1;
			break;
		case 241:
			env->data_bus[231] = tmp;
			return 1;
			break;
		case 242:
			env->data_bus[232] = tmp;
			return 1;
			break;
		case 243:
			env->data_bus[233] = tmp;
			return 1;
			break;
		case 244:
			env->data_bus[234] = tmp;
			return 1;
			break;
		case 245:
			env->data_bus[235] = tmp;
			return 1;
			break;
		case 246:
			env->data_bus[236] = tmp;
			return 1;
			break;
		case 247:
			env->data_bus[237] = tmp;
			return 1;
			break;
		case 248:
			env->data_bus[238] = tmp;
			return 1;
			break;
		case 249:
			env->data_bus[239] = tmp;
			return 1;
			break;
		case 250:
			env->data_bus[240] = tmp;
			return 1;
			break;
		case 251:
			env->data_bus[241] = tmp;
			return 1;
			break;
		case 252:
			env->data_bus[242] = tmp;
			return 1;
			break;
		case 253:
			env->data_bus[243] = tmp;
			return 1;
			break;
		case 254:
			env->data_bus[244] = tmp;
			return 1;
			break;
		case 255:
			env->data_bus[245] = tmp;
			return 1;
			break;
		case 256:
			env->data_bus[246] = tmp;
			return 1;
			break;
		case 257:
			env->data_bus[247] = tmp;
			return 1;
			break;
		case 258:
			env->data_bus[248] = tmp;
			return 1;
			break;
		case 259:
			env->data_bus[249] = tmp;
			return 1;
			break;
		case 260:
			env->data_bus[250] = tmp;
			return 1;
			break;
		case 261:
			env->data_bus[251] = tmp;
			return 1;
			break;
		case 262:
			env->data_bus[252] = tmp;
			return 1;
			break;
		case 263:
			env->data_bus[253] = tmp;
			return 1;
			break;
		case 264:
			env->data_bus[254] = tmp;
			return 1;
			break;
		case 265:
			env->data_bus[255] = tmp;
			return 1;
			break;
		case 266:
			env->data_bus[256] = tmp;
			return 1;
			break;
		case 267:
			env->data_bus[257] = tmp;
			return 1;
			break;
		case 268:
			env->data_bus[258] = tmp;
			return 1;
			break;
		case 269:
			env->data_bus[259] = tmp;
			return 1;
			break;
		case 270:
			env->data_bus[260] = tmp;
			return 1;
			break;
		case 271:
			env->data_bus[261] = tmp;
			return 1;
			break;
		case 272:
			env->data_bus[262] = tmp;
			return 1;
			break;
		case 273:
			env->data_bus[263] = tmp;
			return 1;
			break;
		case 274:
			env->data_bus[264] = tmp;
			return 1;
			break;
		case 275:
			env->data_bus[265] = tmp;
			return 1;
			break;
		case 276:
			env->data_bus[266] = tmp;
			return 1;
			break;
		case 277:
			env->data_bus[267] = tmp;
			return 1;
			break;
		case 278:
			env->data_bus[268] = tmp;
			return 1;
			break;
		case 279:
			env->data_bus[269] = tmp;
			return 1;
			break;
		case 280:
			env->data_bus[270] = tmp;
			return 1;
			break;
		case 281:
			env->data_bus[271] = tmp;
			return 1;
			break;
		case 282:
			env->data_bus[272] = tmp;
			return 1;
			break;
		case 283:
			env->data_bus[273] = tmp;
			return 1;
			break;
		case 284:
			env->data_bus[274] = tmp;
			return 1;
			break;
		case 285:
			env->data_bus[275] = tmp;
			return 1;
			break;
		case 286:
			env->data_bus[276] = tmp;
			return 1;
			break;
		case 287:
			env->data_bus[277] = tmp;
			return 1;
			break;
		case 288:
			env->data_bus[278] = tmp;
			return 1;
			break;
		case 289:
			env->data_bus[279] = tmp;
			return 1;
			break;
		case 290:
			env->data_bus[280] = tmp;
			return 1;
			break;
		case 291:
			env->data_bus[281] = tmp;
			return 1;
			break;
		case 292:
			env->data_bus[282] = tmp;
			return 1;
			break;
		case 293:
			env->data_bus[283] = tmp;
			return 1;
			break;
		case 294:
			env->data_bus[284] = tmp;
			return 1;
			break;
		case 295:
			env->data_bus[285] = tmp;
			return 1;
			break;
		case 296:
			env->data_bus[286] = tmp;
			return 1;
			break;
		case 297:
			env->data_bus[287] = tmp;
			return 1;
			break;
		case 298:
			env->data_bus[288] = tmp;
			return 1;
			break;
		case 299:
			env->data_bus[289] = tmp;
			return 1;
			break;
		case 300:
			env->data_bus[290] = tmp;
			return 1;
			break;
		case 301:
			env->data_bus[291] = tmp;
			return 1;
			break;
		case 302:
			env->data_bus[292] = tmp;
			return 1;
			break;
		case 303:
			env->data_bus[293] = tmp;
			return 1;
			break;
		case 304:
			env->data_bus[294] = tmp;
			return 1;
			break;
		case 305:
			env->data_bus[295] = tmp;
			return 1;
			break;
		case 306:
			env->data_bus[296] = tmp;
			return 1;
			break;
		case 307:
			env->data_bus[297] = tmp;
			return 1;
			break;
		case 308:
			env->data_bus[298] = tmp;
			return 1;
			break;
		case 309:
			env->data_bus[299] = tmp;
			return 1;
			break;
		case 310:
			env->data_bus[300] = tmp;
			return 1;
			break;
		case 311:
			env->data_bus[301] = tmp;
			return 1;
			break;
		case 312:
			env->data_bus[302] = tmp;
			return 1;
			break;
		case 313:
			env->data_bus[303] = tmp;
			return 1;
			break;
		case 314:
			env->data_bus[304] = tmp;
			return 1;
			break;
		case 315:
			env->data_bus[305] = tmp;
			return 1;
			break;
		case 316:
			env->data_bus[306] = tmp;
			return 1;
			break;
		case 317:
			env->data_bus[307] = tmp;
			return 1;
			break;
		case 318:
			env->data_bus[308] = tmp;
			return 1;
			break;
		case 319:
			env->data_bus[309] = tmp;
			return 1;
			break;
		case 320:
			env->data_bus[310] = tmp;
			return 1;
			break;
		case 321:
			env->data_bus[311] = tmp;
			return 1;
			break;
		case 322:
			env->data_bus[312] = tmp;
			return 1;
			break;
		case 323:
			env->data_bus[313] = tmp;
			return 1;
			break;
		case 324:
			env->data_bus[314] = tmp;
			return 1;
			break;
		case 325:
			env->data_bus[315] = tmp;
			return 1;
			break;
		case 326:
			env->data_bus[316] = tmp;
			return 1;
			break;
		case 327:
			env->data_bus[317] = tmp;
			return 1;
			break;
		case 328:
			env->data_bus[318] = tmp;
			return 1;
			break;
		case 329:
			env->data_bus[319] = tmp;
			return 1;
			break;
		case 330:
			env->data_bus[320] = tmp;
			return 1;
			break;
		case 331:
			env->data_bus[321] = tmp;
			return 1;
			break;
		case 332:
			env->data_bus[322] = tmp;
			return 1;
			break;
		case 333:
			env->data_bus[323] = tmp;
			return 1;
			break;
		case 334:
			env->data_bus[324] = tmp;
			return 1;
			break;
		case 335:
			env->data_bus[325] = tmp;
			return 1;
			break;
		case 336:
			env->data_bus[326] = tmp;
			return 1;
			break;
		case 337:
			env->data_bus[327] = tmp;
			return 1;
			break;
		case 338:
			env->data_bus[328] = tmp;
			return 1;
			break;
		case 339:
			env->data_bus[329] = tmp;
			return 1;
			break;
		case 340:
			env->data_bus[330] = tmp;
			return 1;
			break;
		case 341:
			env->data_bus[331] = tmp;
			return 1;
			break;
		case 342:
			env->data_bus[332] = tmp;
			return 1;
			break;
		case 343:
			env->data_bus[333] = tmp;
			return 1;
			break;
		case 344:
			env->data_bus[334] = tmp;
			return 1;
			break;
		case 345:
			env->data_bus[335] = tmp;
			return 1;
			break;
		case 346:
			env->data_bus[336] = tmp;
			return 1;
			break;
		case 347:
			env->data_bus[337] = tmp;
			return 1;
			break;
		case 348:
			env->data_bus[338] = tmp;
			return 1;
			break;
		case 349:
			env->data_bus[339] = tmp;
			return 1;
			break;
		case 350:
			env->data_bus[340] = tmp;
			return 1;
			break;
		case 351:
			env->data_bus[341] = tmp;
			return 1;
			break;
		case 352:
			env->data_bus[342] = tmp;
			return 1;
			break;
		case 353:
			env->data_bus[343] = tmp;
			return 1;
			break;
		case 354:
			env->data_bus[344] = tmp;
			return 1;
			break;
		case 355:
			env->data_bus[345] = tmp;
			return 1;
			break;
		case 356:
			env->data_bus[346] = tmp;
			return 1;
			break;
		case 357:
			env->data_bus[347] = tmp;
			return 1;
			break;
		case 358:
			env->data_bus[348] = tmp;
			return 1;
			break;
		case 359:
			env->data_bus[349] = tmp;
			return 1;
			break;
		case 360:
			env->data_bus[350] = tmp;
			return 1;
			break;
		case 361:
			env->data_bus[351] = tmp;
			return 1;
			break;
		case 362:
			env->data_bus[352] = tmp;
			return 1;
			break;
		case 363:
			env->data_bus[353] = tmp;
			return 1;
			break;
		case 364:
			env->data_bus[354] = tmp;
			return 1;
			break;
		case 365:
			env->data_bus[355] = tmp;
			return 1;
			break;
		case 366:
			env->data_bus[356] = tmp;
			return 1;
			break;
		case 367:
			env->data_bus[357] = tmp;
			return 1;
			break;
		case 368:
			env->data_bus[358] = tmp;
			return 1;
			break;
		case 369:
			env->data_bus[359] = tmp;
			return 1;
			break;
		case 370:
			env->data_bus[360] = tmp;
			return 1;
			break;
		case 371:
			env->data_bus[361] = tmp;
			return 1;
			break;
		case 372:
			env->data_bus[362] = tmp;
			return 1;
			break;
		case 373:
			env->data_bus[363] = tmp;
			return 1;
			break;
		case 374:
			env->data_bus[364] = tmp;
			return 1;
			break;
		case 375:
			env->data_bus[365] = tmp;
			return 1;
			break;
		case 376:
			env->data_bus[366] = tmp;
			return 1;
			break;
		case 377:
			env->data_bus[367] = tmp;
			return 1;
			break;
		case 378:
			env->data_bus[368] = tmp;
			return 1;
			break;
		case 379:
			env->data_bus[369] = tmp;
			return 1;
			break;
		case 380:
			env->data_bus[370] = tmp;
			return 1;
			break;
		case 381:
			env->data_bus[371] = tmp;
			return 1;
			break;
		case 382:
			env->data_bus[372] = tmp;
			return 1;
			break;
		case 383:
			env->data_bus[373] = tmp;
			return 1;
			break;
		case 384:
			env->data_bus[374] = tmp;
			return 1;
			break;
		case 385:
			env->data_bus[375] = tmp;
			return 1;
			break;
		case 386:
			env->data_bus[376] = tmp;
			return 1;
			break;
		case 387:
			env->data_bus[377] = tmp;
			return 1;
			break;
		case 388:
			env->data_bus[378] = tmp;
			return 1;
			break;
		case 389:
			env->data_bus[379] = tmp;
			return 1;
			break;
		case 390:
			env->data_bus[380] = tmp;
			return 1;
			break;
		case 391:
			env->data_bus[381] = tmp;
			return 1;
			break;
		case 392:
			env->data_bus[382] = tmp;
			return 1;
			break;
		case 393:
			env->data_bus[383] = tmp;
			return 1;
			break;
		case 394:
			env->data_bus[384] = tmp;
			return 1;
			break;
		case 395:
			env->data_bus[385] = tmp;
			return 1;
			break;
		case 396:
			env->data_bus[386] = tmp;
			return 1;
			break;
		case 397:
			env->data_bus[387] = tmp;
			return 1;
			break;
		case 398:
			env->data_bus[388] = tmp;
			return 1;
			break;
		case 399:
			env->data_bus[389] = tmp;
			return 1;
			break;
		case 400:
			env->data_bus[390] = tmp;
			return 1;
			break;
		case 401:
			env->data_bus[391] = tmp;
			return 1;
			break;
		case 402:
			env->data_bus[392] = tmp;
			return 1;
			break;
		case 403:
			env->data_bus[393] = tmp;
			return 1;
			break;
		case 404:
			env->data_bus[394] = tmp;
			return 1;
			break;
		case 405:
			env->data_bus[395] = tmp;
			return 1;
			break;
		case 406:
			env->data_bus[396] = tmp;
			return 1;
			break;
		case 407:
			env->data_bus[397] = tmp;
			return 1;
			break;
		case 408:
			env->data_bus[398] = tmp;
			return 1;
			break;
		case 409:
			env->data_bus[399] = tmp;
			return 1;
			break;
		case 410:
			env->data_bus[400] = tmp;
			return 1;
			break;
		case 411:
			env->data_bus[401] = tmp;
			return 1;
			break;
		case 412:
			env->data_bus[402] = tmp;
			return 1;
			break;
		case 413:
			env->data_bus[403] = tmp;
			return 1;
			break;
		case 414:
			env->data_bus[404] = tmp;
			return 1;
			break;
		case 415:
			env->data_bus[405] = tmp;
			return 1;
			break;
		case 416:
			env->data_bus[406] = tmp;
			return 1;
			break;
		case 417:
			env->data_bus[407] = tmp;
			return 1;
			break;
		case 418:
			env->data_bus[408] = tmp;
			return 1;
			break;
		case 419:
			env->data_bus[409] = tmp;
			return 1;
			break;
		case 420:
			env->data_bus[410] = tmp;
			return 1;
			break;
		case 421:
			env->data_bus[411] = tmp;
			return 1;
			break;
		case 422:
			env->data_bus[412] = tmp;
			return 1;
			break;
		case 423:
			env->data_bus[413] = tmp;
			return 1;
			break;
		case 424:
			env->data_bus[414] = tmp;
			return 1;
			break;
		case 425:
			env->data_bus[415] = tmp;
			return 1;
			break;
		case 426:
			env->data_bus[416] = tmp;
			return 1;
			break;
		case 427:
			env->data_bus[417] = tmp;
			return 1;
			break;
		case 428:
			env->data_bus[418] = tmp;
			return 1;
			break;
		case 429:
			env->data_bus[419] = tmp;
			return 1;
			break;
		case 430:
			env->data_bus[420] = tmp;
			return 1;
			break;
		case 431:
			env->data_bus[421] = tmp;
			return 1;
			break;
		case 432:
			env->data_bus[422] = tmp;
			return 1;
			break;
		case 433:
			env->data_bus[423] = tmp;
			return 1;
			break;
		case 434:
			env->data_bus[424] = tmp;
			return 1;
			break;
		case 435:
			env->data_bus[425] = tmp;
			return 1;
			break;
		case 436:
			env->data_bus[426] = tmp;
			return 1;
			break;
		case 437:
			env->data_bus[427] = tmp;
			return 1;
			break;
		case 438:
			env->data_bus[428] = tmp;
			return 1;
			break;
		case 439:
			env->data_bus[429] = tmp;
			return 1;
			break;
		case 440:
			env->data_bus[430] = tmp;
			return 1;
			break;
		case 441:
			env->data_bus[431] = tmp;
			return 1;
			break;
		case 442:
			env->data_bus[432] = tmp;
			return 1;
			break;
		case 443:
			env->data_bus[433] = tmp;
			return 1;
			break;
		case 444:
			env->data_bus[434] = tmp;
			return 1;
			break;
		case 445:
			env->data_bus[435] = tmp;
			return 1;
			break;
		case 446:
			env->data_bus[436] = tmp;
			return 1;
			break;
		case 447:
			env->data_bus[437] = tmp;
			return 1;
			break;
		case 448:
			env->data_bus[438] = tmp;
			return 1;
			break;
		case 449:
			env->data_bus[439] = tmp;
			return 1;
			break;
		case 450:
			env->data_bus[440] = tmp;
			return 1;
			break;
		case 451:
			env->data_bus[441] = tmp;
			return 1;
			break;
		case 452:
			env->data_bus[442] = tmp;
			return 1;
			break;
		case 453:
			env->data_bus[443] = tmp;
			return 1;
			break;
		case 454:
			env->data_bus[444] = tmp;
			return 1;
			break;
		case 455:
			env->data_bus[445] = tmp;
			return 1;
			break;
		case 456:
			env->data_bus[446] = tmp;
			return 1;
			break;
		case 457:
			env->data_bus[447] = tmp;
			return 1;
			break;
		case 458:
			env->data_bus[448] = tmp;
			return 1;
			break;
		case 459:
			env->data_bus[449] = tmp;
			return 1;
			break;
		case 460:
			env->data_bus[450] = tmp;
			return 1;
			break;
		case 461:
			env->data_bus[451] = tmp;
			return 1;
			break;
		case 462:
			env->data_bus[452] = tmp;
			return 1;
			break;
		case 463:
			env->data_bus[453] = tmp;
			return 1;
			break;
		case 464:
			env->data_bus[454] = tmp;
			return 1;
			break;
		case 465:
			env->data_bus[455] = tmp;
			return 1;
			break;
		case 466:
			env->data_bus[456] = tmp;
			return 1;
			break;
		case 467:
			env->data_bus[457] = tmp;
			return 1;
			break;
		case 468:
			env->data_bus[458] = tmp;
			return 1;
			break;
		case 469:
			env->data_bus[459] = tmp;
			return 1;
			break;
		case 470:
			env->data_bus[460] = tmp;
			return 1;
			break;
		case 471:
			env->data_bus[461] = tmp;
			return 1;
			break;
		case 472:
			env->data_bus[462] = tmp;
			return 1;
			break;
		case 473:
			env->data_bus[463] = tmp;
			return 1;
			break;
		case 474:
			env->data_bus[464] = tmp;
			return 1;
			break;
		case 475:
			env->data_bus[465] = tmp;
			return 1;
			break;
		case 476:
			env->data_bus[466] = tmp;
			return 1;
			break;
		case 477:
			env->data_bus[467] = tmp;
			return 1;
			break;
		case 478:
			env->data_bus[468] = tmp;
			return 1;
			break;
		case 479:
			env->data_bus[469] = tmp;
			return 1;
			break;
		case 480:
			env->data_bus[470] = tmp;
			return 1;
			break;
		case 481:
			env->data_bus[471] = tmp;
			return 1;
			break;
		case 482:
			env->data_bus[472] = tmp;
			return 1;
			break;
		case 483:
			env->data_bus[473] = tmp;
			return 1;
			break;
		case 484:
			env->data_bus[474] = tmp;
			return 1;
			break;
		case 485:
			env->data_bus[475] = tmp;
			return 1;
			break;
		case 486:
			env->data_bus[476] = tmp;
			return 1;
			break;
		case 487:
			env->data_bus[477] = tmp;
			return 1;
			break;
		case 488:
			env->data_bus[478] = tmp;
			return 1;
			break;
		case 489:
			env->data_bus[479] = tmp;
			return 1;
			break;
		case 490:
			env->data_bus[480] = tmp;
			return 1;
			break;
		case 491:
			env->data_bus[481] = tmp;
			return 1;
			break;
		case 492:
			env->data_bus[482] = tmp;
			return 1;
			break;
		case 493:
			env->data_bus[483] = tmp;
			return 1;
			break;
		case 494:
			env->data_bus[484] = tmp;
			return 1;
			break;
		case 495:
			env->data_bus[485] = tmp;
			return 1;
			break;
		case 496:
			env->data_bus[486] = tmp;
			return 1;
			break;
		case 497:
			env->data_bus[487] = tmp;
			return 1;
			break;
		case 498:
			env->data_bus[488] = tmp;
			return 1;
			break;
		case 499:
			env->data_bus[489] = tmp;
			return 1;
			break;
		case 500:
			env->data_bus[490] = tmp;
			return 1;
			break;
		case 501:
			env->data_bus[491] = tmp;
			return 1;
			break;
		case 502:
			env->data_bus[492] = tmp;
			return 1;
			break;
		case 503:
			env->data_bus[493] = tmp;
			return 1;
			break;
		case 504:
			env->data_bus[494] = tmp;
			return 1;
			break;
		case 505:
			env->data_bus[495] = tmp;
			return 1;
			break;
		case 506:
			env->data_bus[496] = tmp;
			return 1;
			break;
		case 507:
			env->data_bus[497] = tmp;
			return 1;
			break;
		case 508:
			env->data_bus[498] = tmp;
			return 1;
			break;
		case 509:
			env->data_bus[499] = tmp;
			return 1;
			break;
		case 510:
			env->data_bus[500] = tmp;
			return 1;
			break;
		case 511:
			env->data_bus[501] = tmp;
			return 1;
			break;
		case 512:
			env->data_bus[502] = tmp;
			return 1;
			break;
		case 513:
			env->data_bus[503] = tmp;
			return 1;
			break;
		case 514:
			env->data_bus[504] = tmp;
			return 1;
			break;
		case 515:
			env->data_bus[505] = tmp;
			return 1;
			break;
		case 516:
			env->data_bus[506] = tmp;
			return 1;
			break;
		case 517:
			env->data_bus[507] = tmp;
			return 1;
			break;
		case 518:
			env->data_bus[508] = tmp;
			return 1;
			break;
		case 519:
			env->data_bus[509] = tmp;
			return 1;
			break;
		case 520:
			env->data_bus[510] = tmp;
			return 1;
			break;
		case 521:
			env->data_bus[511] = tmp;
			return 1;
			break;
		case 522:
			env->data_bus[512] = tmp;
			return 1;
			break;
		case 523:
			env->data_bus[513] = tmp;
			return 1;
			break;
		case 524:
			env->data_bus[514] = tmp;
			return 1;
			break;
		case 525:
			env->data_bus[515] = tmp;
			return 1;
			break;
		case 526:
			env->data_bus[516] = tmp;
			return 1;
			break;
		case 527:
			env->data_bus[517] = tmp;
			return 1;
			break;
		case 528:
			env->data_bus[518] = tmp;
			return 1;
			break;
		case 529:
			env->data_bus[519] = tmp;
			return 1;
			break;
		case 530:
			env->data_bus[520] = tmp;
			return 1;
			break;
		case 531:
			env->data_bus[521] = tmp;
			return 1;
			break;
		case 532:
			env->data_bus[522] = tmp;
			return 1;
			break;
		case 533:
			env->data_bus[523] = tmp;
			return 1;
			break;
		case 534:
			env->data_bus[524] = tmp;
			return 1;
			break;
		case 535:
			env->data_bus[525] = tmp;
			return 1;
			break;
		case 536:
			env->data_bus[526] = tmp;
			return 1;
			break;
		case 537:
			env->data_bus[527] = tmp;
			return 1;
			break;
		case 538:
			env->data_bus[528] = tmp;
			return 1;
			break;
		case 539:
			env->data_bus[529] = tmp;
			return 1;
			break;
		case 540:
			env->data_bus[530] = tmp;
			return 1;
			break;
		case 541:
			env->data_bus[531] = tmp;
			return 1;
			break;
		case 542:
			env->data_bus[532] = tmp;
			return 1;
			break;
		case 543:
			env->data_bus[533] = tmp;
			return 1;
			break;
		case 544:
			env->data_bus[534] = tmp;
			return 1;
			break;
		case 545:
			env->data_bus[535] = tmp;
			return 1;
			break;
		case 546:
			env->data_bus[536] = tmp;
			return 1;
			break;
		case 547:
			env->data_bus[537] = tmp;
			return 1;
			break;
		case 548:
			env->data_bus[538] = tmp;
			return 1;
			break;
		case 549:
			env->data_bus[539] = tmp;
			return 1;
			break;
		case 550:
			env->data_bus[540] = tmp;
			return 1;
			break;
		case 551:
			env->data_bus[541] = tmp;
			return 1;
			break;
		case 552:
			env->data_bus[542] = tmp;
			return 1;
			break;
		case 553:
			env->data_bus[543] = tmp;
			return 1;
			break;
		case 554:
			env->data_bus[544] = tmp;
			return 1;
			break;
		case 555:
			env->data_bus[545] = tmp;
			return 1;
			break;
		case 556:
			env->data_bus[546] = tmp;
			return 1;
			break;
		case 557:
			env->data_bus[547] = tmp;
			return 1;
			break;
		case 558:
			env->data_bus[548] = tmp;
			return 1;
			break;
		case 559:
			env->data_bus[549] = tmp;
			return 1;
			break;
		case 560:
			env->data_bus[550] = tmp;
			return 1;
			break;
		case 561:
			env->data_bus[551] = tmp;
			return 1;
			break;
		case 562:
			env->data_bus[552] = tmp;
			return 1;
			break;
		case 563:
			env->data_bus[553] = tmp;
			return 1;
			break;
		case 564:
			env->data_bus[554] = tmp;
			return 1;
			break;
		case 565:
			env->data_bus[555] = tmp;
			return 1;
			break;
		case 566:
			env->data_bus[556] = tmp;
			return 1;
			break;
		case 567:
			env->data_bus[557] = tmp;
			return 1;
			break;
		case 568:
			env->data_bus[558] = tmp;
			return 1;
			break;
		case 569:
			env->data_bus[559] = tmp;
			return 1;
			break;
		case 570:
			env->data_bus[560] = tmp;
			return 1;
			break;
		case 571:
			env->data_bus[561] = tmp;
			return 1;
			break;
		case 572:
			env->data_bus[562] = tmp;
			return 1;
			break;
		case 573:
			env->data_bus[563] = tmp;
			return 1;
			break;
		case 574:
			env->data_bus[564] = tmp;
			return 1;
			break;
		case 575:
			env->data_bus[565] = tmp;
			return 1;
			break;
		case 576:
			env->data_bus[566] = tmp;
			return 1;
			break;
		case 577:
			env->data_bus[567] = tmp;
			return 1;
			break;
		case 578:
			env->data_bus[568] = tmp;
			return 1;
			break;
		case 579:
			env->data_bus[569] = tmp;
			return 1;
			break;
		case 580:
			env->data_bus[570] = tmp;
			return 1;
			break;
		case 581:
			env->data_bus[571] = tmp;
			return 1;
			break;
		case 582:
			env->data_bus[572] = tmp;
			return 1;
			break;
		case 583:
			env->data_bus[573] = tmp;
			return 1;
			break;
		case 584:
			env->data_bus[574] = tmp;
			return 1;
			break;
		case 585:
			env->data_bus[575] = tmp;
			return 1;
			break;
		case 586:
			env->data_bus[576] = tmp;
			return 1;
			break;
		case 587:
			env->data_bus[577] = tmp;
			return 1;
			break;
		case 588:
			env->data_bus[578] = tmp;
			return 1;
			break;
		case 589:
			env->data_bus[579] = tmp;
			return 1;
			break;
		case 590:
			env->data_bus[580] = tmp;
			return 1;
			break;
		case 591:
			env->data_bus[581] = tmp;
			return 1;
			break;
		case 592:
			env->data_bus[582] = tmp;
			return 1;
			break;
		case 593:
			env->data_bus[583] = tmp;
			return 1;
			break;
		case 594:
			env->data_bus[584] = tmp;
			return 1;
			break;
		case 595:
			env->data_bus[585] = tmp;
			return 1;
			break;
		case 596:
			env->data_bus[586] = tmp;
			return 1;
			break;
		case 597:
			env->data_bus[587] = tmp;
			return 1;
			break;
		case 598:
			env->data_bus[588] = tmp;
			return 1;
			break;
		case 599:
			env->data_bus[589] = tmp;
			return 1;
			break;
		case 600:
			env->data_bus[590] = tmp;
			return 1;
			break;
		case 601:
			env->data_bus[591] = tmp;
			return 1;
			break;
		case 602:
			env->data_bus[592] = tmp;
			return 1;
			break;
		case 603:
			env->data_bus[593] = tmp;
			return 1;
			break;
		case 604:
			env->data_bus[594] = tmp;
			return 1;
			break;
		case 605:
			env->data_bus[595] = tmp;
			return 1;
			break;
		case 606:
			env->data_bus[596] = tmp;
			return 1;
			break;
		case 607:
			env->data_bus[597] = tmp;
			return 1;
			break;
		case 608:
			env->data_bus[598] = tmp;
			return 1;
			break;
		case 609:
			env->data_bus[599] = tmp;
			return 1;
			break;
		case 610:
			env->data_bus[600] = tmp;
			return 1;
			break;
		case 611:
			env->data_bus[601] = tmp;
			return 1;
			break;
		case 612:
			env->data_bus[602] = tmp;
			return 1;
			break;
		case 613:
			env->data_bus[603] = tmp;
			return 1;
			break;
		case 614:
			env->data_bus[604] = tmp;
			return 1;
			break;
		case 615:
			env->data_bus[605] = tmp;
			return 1;
			break;
		case 616:
			env->data_bus[606] = tmp;
			return 1;
			break;
		case 617:
			env->data_bus[607] = tmp;
			return 1;
			break;
		case 618:
			env->data_bus[608] = tmp;
			return 1;
			break;
		case 619:
			env->data_bus[609] = tmp;
			return 1;
			break;
		case 620:
			env->data_bus[610] = tmp;
			return 1;
			break;
		case 621:
			env->data_bus[611] = tmp;
			return 1;
			break;
		case 622:
			env->data_bus[612] = tmp;
			return 1;
			break;
		case 623:
			env->data_bus[613] = tmp;
			return 1;
			break;
		case 624:
			env->data_bus[614] = tmp;
			return 1;
			break;
		case 625:
			env->data_bus[615] = tmp;
			return 1;
			break;
		case 626:
			env->data_bus[616] = tmp;
			return 1;
			break;
		case 627:
			env->data_bus[617] = tmp;
			return 1;
			break;
		case 628:
			env->data_bus[618] = tmp;
			return 1;
			break;
		case 629:
			env->data_bus[619] = tmp;
			return 1;
			break;
		case 630:
			env->data_bus[620] = tmp;
			return 1;
			break;
		case 631:
			env->data_bus[621] = tmp;
			return 1;
			break;
		case 632:
			env->data_bus[622] = tmp;
			return 1;
			break;
		case 633:
			env->data_bus[623] = tmp;
			return 1;
			break;
		case 634:
			env->data_bus[624] = tmp;
			return 1;
			break;
		case 635:
			env->data_bus[625] = tmp;
			return 1;
			break;
		case 636:
			env->data_bus[626] = tmp;
			return 1;
			break;
		case 637:
			env->data_bus[627] = tmp;
			return 1;
			break;
		case 638:
			env->data_bus[628] = tmp;
			return 1;
			break;
		case 639:
			env->data_bus[629] = tmp;
			return 1;
			break;
		case 640:
			env->data_bus[630] = tmp;
			return 1;
			break;
		case 641:
			env->data_bus[631] = tmp;
			return 1;
			break;
		case 642:
			env->data_bus[632] = tmp;
			return 1;
			break;
		case 643:
			env->data_bus[633] = tmp;
			return 1;
			break;
		case 644:
			env->data_bus[634] = tmp;
			return 1;
			break;
		case 645:
			env->data_bus[635] = tmp;
			return 1;
			break;
		case 646:
			env->data_bus[636] = tmp;
			return 1;
			break;
		case 647:
			env->data_bus[637] = tmp;
			return 1;
			break;
		case 648:
			env->data_bus[638] = tmp;
			return 1;
			break;
		case 649:
			env->data_bus[639] = tmp;
			return 1;
			break;
		case 650:
			env->data_bus[640] = tmp;
			return 1;
			break;
		case 651:
			env->data_bus[641] = tmp;
			return 1;
			break;
		case 652:
			env->data_bus[642] = tmp;
			return 1;
			break;
		case 653:
			env->data_bus[643] = tmp;
			return 1;
			break;
		case 654:
			env->data_bus[644] = tmp;
			return 1;
			break;
		case 655:
			env->data_bus[645] = tmp;
			return 1;
			break;
		case 656:
			env->data_bus[646] = tmp;
			return 1;
			break;
		case 657:
			env->data_bus[647] = tmp;
			return 1;
			break;
		case 658:
			env->data_bus[648] = tmp;
			return 1;
			break;
		case 659:
			env->data_bus[649] = tmp;
			return 1;
			break;
		case 660:
			env->data_bus[650] = tmp;
			return 1;
			break;
		case 661:
			env->data_bus[651] = tmp;
			return 1;
			break;
		case 662:
			env->data_bus[652] = tmp;
			return 1;
			break;
		case 663:
			env->data_bus[653] = tmp;
			return 1;
			break;
		case 664:
			env->data_bus[654] = tmp;
			return 1;
			break;
		case 665:
			env->data_bus[655] = tmp;
			return 1;
			break;
		case 666:
			env->data_bus[656] = tmp;
			return 1;
			break;
		case 667:
			env->data_bus[657] = tmp;
			return 1;
			break;
		case 668:
			env->data_bus[658] = tmp;
			return 1;
			break;
		case 669:
			env->data_bus[659] = tmp;
			return 1;
			break;
		case 670:
			env->data_bus[660] = tmp;
			return 1;
			break;
		case 671:
			env->data_bus[661] = tmp;
			return 1;
			break;
		case 672:
			env->data_bus[662] = tmp;
			return 1;
			break;
		case 673:
			env->data_bus[663] = tmp;
			return 1;
			break;
		case 674:
			env->data_bus[664] = tmp;
			return 1;
			break;
		case 675:
			env->data_bus[665] = tmp;
			return 1;
			break;
		case 676:
			env->data_bus[666] = tmp;
			return 1;
			break;
		case 677:
			env->data_bus[667] = tmp;
			return 1;
			break;
		case 678:
			env->data_bus[668] = tmp;
			return 1;
			break;
		case 679:
			env->data_bus[669] = tmp;
			return 1;
			break;
		case 680:
			env->data_bus[670] = tmp;
			return 1;
			break;
		case 681:
			env->data_bus[671] = tmp;
			return 1;
			break;
		case 682:
			env->data_bus[672] = tmp;
			return 1;
			break;
		case 683:
			env->data_bus[673] = tmp;
			return 1;
			break;
		case 684:
			env->data_bus[674] = tmp;
			return 1;
			break;
		case 685:
			env->data_bus[675] = tmp;
			return 1;
			break;
		case 686:
			env->data_bus[676] = tmp;
			return 1;
			break;
		case 687:
			env->data_bus[677] = tmp;
			return 1;
			break;
		case 688:
			env->data_bus[678] = tmp;
			return 1;
			break;
		case 689:
			env->data_bus[679] = tmp;
			return 1;
			break;
		case 690:
			env->data_bus[680] = tmp;
			return 1;
			break;
		case 691:
			env->data_bus[681] = tmp;
			return 1;
			break;
		case 692:
			env->data_bus[682] = tmp;
			return 1;
			break;
		case 693:
			env->data_bus[683] = tmp;
			return 1;
			break;
		case 694:
			env->data_bus[684] = tmp;
			return 1;
			break;
		case 695:
			env->data_bus[685] = tmp;
			return 1;
			break;
		case 696:
			env->data_bus[686] = tmp;
			return 1;
			break;
		case 697:
			env->data_bus[687] = tmp;
			return 1;
			break;
		case 698:
			env->data_bus[688] = tmp;
			return 1;
			break;
		case 699:
			env->data_bus[689] = tmp;
			return 1;
			break;
		case 700:
			env->data_bus[690] = tmp;
			return 1;
			break;
		case 701:
			env->data_bus[691] = tmp;
			return 1;
			break;
		case 702:
			env->data_bus[692] = tmp;
			return 1;
			break;
		case 703:
			env->data_bus[693] = tmp;
			return 1;
			break;
		case 704:
			env->data_bus[694] = tmp;
			return 1;
			break;
		case 705:
			env->data_bus[695] = tmp;
			return 1;
			break;
		case 706:
			env->data_bus[696] = tmp;
			return 1;
			break;
		case 707:
			env->data_bus[697] = tmp;
			return 1;
			break;
		case 708:
			env->data_bus[698] = tmp;
			return 1;
			break;
		case 709:
			env->data_bus[699] = tmp;
			return 1;
			break;
		case 710:
			env->data_bus[700] = tmp;
			return 1;
			break;
		case 711:
			env->data_bus[701] = tmp;
			return 1;
			break;
		case 712:
			env->data_bus[702] = tmp;
			return 1;
			break;
		case 713:
			env->data_bus[703] = tmp;
			return 1;
			break;
		case 714:
			env->data_bus[704] = tmp;
			return 1;
			break;
		case 715:
			env->data_bus[705] = tmp;
			return 1;
			break;
		case 716:
			env->data_bus[706] = tmp;
			return 1;
			break;
		case 717:
			env->data_bus[707] = tmp;
			return 1;
			break;
		case 718:
			env->data_bus[708] = tmp;
			return 1;
			break;
		case 719:
			env->data_bus[709] = tmp;
			return 1;
			break;
		case 720:
			env->data_bus[710] = tmp;
			return 1;
			break;
		case 721:
			env->data_bus[711] = tmp;
			return 1;
			break;
		case 722:
			env->data_bus[712] = tmp;
			return 1;
			break;
		case 723:
			env->data_bus[713] = tmp;
			return 1;
			break;
		case 724:
			env->data_bus[714] = tmp;
			return 1;
			break;
		case 725:
			env->data_bus[715] = tmp;
			return 1;
			break;
		case 726:
			env->data_bus[716] = tmp;
			return 1;
			break;
		case 727:
			env->data_bus[717] = tmp;
			return 1;
			break;
		case 728:
			env->data_bus[718] = tmp;
			return 1;
			break;
		case 729:
			env->data_bus[719] = tmp;
			return 1;
			break;
		case 730:
			env->data_bus[720] = tmp;
			return 1;
			break;
		case 731:
			env->data_bus[721] = tmp;
			return 1;
			break;
		case 732:
			env->data_bus[722] = tmp;
			return 1;
			break;
		case 733:
			env->data_bus[723] = tmp;
			return 1;
			break;
		case 734:
			env->data_bus[724] = tmp;
			return 1;
			break;
		case 735:
			env->data_bus[725] = tmp;
			return 1;
			break;
		case 736:
			env->data_bus[726] = tmp;
			return 1;
			break;
		case 737:
			env->data_bus[727] = tmp;
			return 1;
			break;
		case 738:
			env->data_bus[728] = tmp;
			return 1;
			break;
		case 739:
			env->data_bus[729] = tmp;
			return 1;
			break;
		case 740:
			env->data_bus[730] = tmp;
			return 1;
			break;
		case 741:
			env->data_bus[731] = tmp;
			return 1;
			break;
		case 742:
			env->data_bus[732] = tmp;
			return 1;
			break;
		case 743:
			env->data_bus[733] = tmp;
			return 1;
			break;
		case 744:
			env->data_bus[734] = tmp;
			return 1;
			break;
		case 745:
			env->data_bus[735] = tmp;
			return 1;
			break;
		case 746:
			env->data_bus[736] = tmp;
			return 1;
			break;
		case 747:
			env->data_bus[737] = tmp;
			return 1;
			break;
		case 748:
			env->data_bus[738] = tmp;
			return 1;
			break;
		case 749:
			env->data_bus[739] = tmp;
			return 1;
			break;
		case 750:
			env->data_bus[740] = tmp;
			return 1;
			break;
		case 751:
			env->data_bus[741] = tmp;
			return 1;
			break;
		case 752:
			env->data_bus[742] = tmp;
			return 1;
			break;
		case 753:
			env->data_bus[743] = tmp;
			return 1;
			break;
		case 754:
			env->data_bus[744] = tmp;
			return 1;
			break;
		case 755:
			env->data_bus[745] = tmp;
			return 1;
			break;
		case 756:
			env->data_bus[746] = tmp;
			return 1;
			break;
		case 757:
			env->data_bus[747] = tmp;
			return 1;
			break;
		case 758:
			env->data_bus[748] = tmp;
			return 1;
			break;
		case 759:
			env->data_bus[749] = tmp;
			return 1;
			break;
		case 760:
			env->data_bus[750] = tmp;
			return 1;
			break;
		case 761:
			env->data_bus[751] = tmp;
			return 1;
			break;
		case 762:
			env->data_bus[752] = tmp;
			return 1;
			break;
		case 763:
			env->data_bus[753] = tmp;
			return 1;
			break;
		case 764:
			env->data_bus[754] = tmp;
			return 1;
			break;
		case 765:
			env->data_bus[755] = tmp;
			return 1;
			break;
		case 766:
			env->data_bus[756] = tmp;
			return 1;
			break;
		case 767:
			env->data_bus[757] = tmp;
			return 1;
			break;
		case 768:
			env->data_bus[758] = tmp;
			return 1;
			break;
		case 769:
			env->data_bus[759] = tmp;
			return 1;
			break;
		case 770:
			env->data_bus[760] = tmp;
			return 1;
			break;
		case 771:
			env->data_bus[761] = tmp;
			return 1;
			break;
		case 772:
			env->data_bus[762] = tmp;
			return 1;
			break;
		case 773:
			env->data_bus[763] = tmp;
			return 1;
			break;
		case 774:
			env->data_bus[764] = tmp;
			return 1;
			break;
		case 775:
			env->data_bus[765] = tmp;
			return 1;
			break;
		case 776:
			env->data_bus[766] = tmp;
			return 1;
			break;
		case 777:
			env->data_bus[767] = tmp;
			return 1;
			break;
		case 778:
			env->data_bus[768] = tmp;
			return 1;
			break;
		case 779:
			env->data_bus[769] = tmp;
			return 1;
			break;
		case 780:
			env->data_bus[770] = tmp;
			return 1;
			break;
		case 781:
			env->data_bus[771] = tmp;
			return 1;
			break;
		case 782:
			env->data_bus[772] = tmp;
			return 1;
			break;
		case 783:
			env->data_bus[773] = tmp;
			return 1;
			break;
		case 784:
			env->data_bus[774] = tmp;
			return 1;
			break;
		case 785:
			env->data_bus[775] = tmp;
			return 1;
			break;
		case 786:
			env->data_bus[776] = tmp;
			return 1;
			break;
		case 787:
			env->data_bus[777] = tmp;
			return 1;
			break;
		case 788:
			env->data_bus[778] = tmp;
			return 1;
			break;
		case 789:
			env->data_bus[779] = tmp;
			return 1;
			break;
		case 790:
			env->data_bus[780] = tmp;
			return 1;
			break;
		case 791:
			env->data_bus[781] = tmp;
			return 1;
			break;
		case 792:
			env->data_bus[782] = tmp;
			return 1;
			break;
		case 793:
			env->data_bus[783] = tmp;
			return 1;
			break;
		case 794:
			env->data_bus[784] = tmp;
			return 1;
			break;
		case 795:
			env->data_bus[785] = tmp;
			return 1;
			break;
		case 796:
			env->data_bus[786] = tmp;
			return 1;
			break;
		case 797:
			env->data_bus[787] = tmp;
			return 1;
			break;
		case 798:
			env->data_bus[788] = tmp;
			return 1;
			break;
		case 799:
			env->data_bus[789] = tmp;
			return 1;
			break;
		case 800:
			env->data_bus[790] = tmp;
			return 1;
			break;
		case 801:
			env->data_bus[791] = tmp;
			return 1;
			break;
		case 802:
			env->data_bus[792] = tmp;
			return 1;
			break;
		case 803:
			env->data_bus[793] = tmp;
			return 1;
			break;
		case 804:
			env->data_bus[794] = tmp;
			return 1;
			break;
		case 805:
			env->data_bus[795] = tmp;
			return 1;
			break;
		case 806:
			env->data_bus[796] = tmp;
			return 1;
			break;
		case 807:
			env->data_bus[797] = tmp;
			return 1;
			break;
		case 808:
			env->data_bus[798] = tmp;
			return 1;
			break;
		case 809:
			env->data_bus[799] = tmp;
			return 1;
			break;
		case 810:
			env->data_bus[800] = tmp;
			return 1;
			break;
		case 811:
			env->data_bus[801] = tmp;
			return 1;
			break;
		case 812:
			env->data_bus[802] = tmp;
			return 1;
			break;
		case 813:
			env->data_bus[803] = tmp;
			return 1;
			break;
		case 814:
			env->data_bus[804] = tmp;
			return 1;
			break;
		case 815:
			env->data_bus[805] = tmp;
			return 1;
			break;
		case 816:
			env->data_bus[806] = tmp;
			return 1;
			break;
		case 817:
			env->data_bus[807] = tmp;
			return 1;
			break;
		case 818:
			env->data_bus[808] = tmp;
			return 1;
			break;
		case 819:
			env->data_bus[809] = tmp;
			return 1;
			break;
		case 820:
			env->data_bus[810] = tmp;
			return 1;
			break;
		case 821:
			env->data_bus[811] = tmp;
			return 1;
			break;
		case 822:
			env->data_bus[812] = tmp;
			return 1;
			break;
		case 823:
			env->data_bus[813] = tmp;
			return 1;
			break;
		case 824:
			env->data_bus[814] = tmp;
			return 1;
			break;
		case 825:
			env->data_bus[815] = tmp;
			return 1;
			break;
		case 826:
			env->data_bus[816] = tmp;
			return 1;
			break;
		case 827:
			env->data_bus[817] = tmp;
			return 1;
			break;
		case 828:
			env->data_bus[818] = tmp;
			return 1;
			break;
		case 829:
			env->data_bus[819] = tmp;
			return 1;
			break;
		case 830:
			env->data_bus[820] = tmp;
			return 1;
			break;
		case 831:
			env->data_bus[821] = tmp;
			return 1;
			break;
		case 832:
			env->data_bus[822] = tmp;
			return 1;
			break;
		case 833:
			env->data_bus[823] = tmp;
			return 1;
			break;
		case 834:
			env->data_bus[824] = tmp;
			return 1;
			break;
		case 835:
			env->data_bus[825] = tmp;
			return 1;
			break;
		case 836:
			env->data_bus[826] = tmp;
			return 1;
			break;
		case 837:
			env->data_bus[827] = tmp;
			return 1;
			break;
		case 838:
			env->data_bus[828] = tmp;
			return 1;
			break;
		case 839:
			env->data_bus[829] = tmp;
			return 1;
			break;
		case 840:
			env->data_bus[830] = tmp;
			return 1;
			break;
		case 841:
			env->data_bus[831] = tmp;
			return 1;
			break;
		case 842:
			env->data_bus[832] = tmp;
			return 1;
			break;
		case 843:
			env->data_bus[833] = tmp;
			return 1;
			break;
		case 844:
			env->data_bus[834] = tmp;
			return 1;
			break;
		case 845:
			env->data_bus[835] = tmp;
			return 1;
			break;
		case 846:
			env->data_bus[836] = tmp;
			return 1;
			break;
		case 847:
			env->data_bus[837] = tmp;
			return 1;
			break;
		case 848:
			env->data_bus[838] = tmp;
			return 1;
			break;
		case 849:
			env->data_bus[839] = tmp;
			return 1;
			break;
		case 850:
			env->data_bus[840] = tmp;
			return 1;
			break;
		case 851:
			env->data_bus[841] = tmp;
			return 1;
			break;
		case 852:
			env->data_bus[842] = tmp;
			return 1;
			break;
		case 853:
			env->data_bus[843] = tmp;
			return 1;
			break;
		case 854:
			env->data_bus[844] = tmp;
			return 1;
			break;
		case 855:
			env->data_bus[845] = tmp;
			return 1;
			break;
		case 856:
			env->data_bus[846] = tmp;
			return 1;
			break;
		case 857:
			env->data_bus[847] = tmp;
			return 1;
			break;
		case 858:
			env->data_bus[848] = tmp;
			return 1;
			break;
		case 859:
			env->data_bus[849] = tmp;
			return 1;
			break;
		case 860:
			env->data_bus[850] = tmp;
			return 1;
			break;
		case 861:
			env->data_bus[851] = tmp;
			return 1;
			break;
		case 862:
			env->data_bus[852] = tmp;
			return 1;
			break;
		case 863:
			env->data_bus[853] = tmp;
			return 1;
			break;
		case 864:
			env->data_bus[854] = tmp;
			return 1;
			break;
		case 865:
			env->data_bus[855] = tmp;
			return 1;
			break;
		case 866:
			env->data_bus[856] = tmp;
			return 1;
			break;
		case 867:
			env->data_bus[857] = tmp;
			return 1;
			break;
		case 868:
			env->data_bus[858] = tmp;
			return 1;
			break;
		case 869:
			env->data_bus[859] = tmp;
			return 1;
			break;
		case 870:
			env->data_bus[860] = tmp;
			return 1;
			break;
		case 871:
			env->data_bus[861] = tmp;
			return 1;
			break;
		case 872:
			env->data_bus[862] = tmp;
			return 1;
			break;
		case 873:
			env->data_bus[863] = tmp;
			return 1;
			break;
		case 874:
			env->data_bus[864] = tmp;
			return 1;
			break;
		case 875:
			env->data_bus[865] = tmp;
			return 1;
			break;
		case 876:
			env->data_bus[866] = tmp;
			return 1;
			break;
		case 877:
			env->data_bus[867] = tmp;
			return 1;
			break;
		case 878:
			env->data_bus[868] = tmp;
			return 1;
			break;
		case 879:
			env->data_bus[869] = tmp;
			return 1;
			break;
		case 880:
			env->data_bus[870] = tmp;
			return 1;
			break;
		case 881:
			env->data_bus[871] = tmp;
			return 1;
			break;
		case 882:
			env->data_bus[872] = tmp;
			return 1;
			break;
		case 883:
			env->data_bus[873] = tmp;
			return 1;
			break;
		case 884:
			env->data_bus[874] = tmp;
			return 1;
			break;
		case 885:
			env->data_bus[875] = tmp;
			return 1;
			break;
		case 886:
			env->data_bus[876] = tmp;
			return 1;
			break;
		case 887:
			env->data_bus[877] = tmp;
			return 1;
			break;
		case 888:
			env->data_bus[878] = tmp;
			return 1;
			break;
		case 889:
			env->data_bus[879] = tmp;
			return 1;
			break;
		case 890:
			env->data_bus[880] = tmp;
			return 1;
			break;
		case 891:
			env->data_bus[881] = tmp;
			return 1;
			break;
		case 892:
			env->data_bus[882] = tmp;
			return 1;
			break;
		case 893:
			env->data_bus[883] = tmp;
			return 1;
			break;
		case 894:
			env->data_bus[884] = tmp;
			return 1;
			break;
		case 895:
			env->data_bus[885] = tmp;
			return 1;
			break;
		case 896:
			env->data_bus[886] = tmp;
			return 1;
			break;
		case 897:
			env->data_bus[887] = tmp;
			return 1;
			break;
		case 898:
			env->data_bus[888] = tmp;
			return 1;
			break;
		case 899:
			env->data_bus[889] = tmp;
			return 1;
			break;
		case 900:
			env->data_bus[890] = tmp;
			return 1;
			break;
		case 901:
			env->data_bus[891] = tmp;
			return 1;
			break;
		case 902:
			env->data_bus[892] = tmp;
			return 1;
			break;
		case 903:
			env->data_bus[893] = tmp;
			return 1;
			break;
		case 904:
			env->data_bus[894] = tmp;
			return 1;
			break;
		case 905:
			env->data_bus[895] = tmp;
			return 1;
			break;
		case 906:
			env->data_bus[896] = tmp;
			return 1;
			break;
		case 907:
			env->data_bus[897] = tmp;
			return 1;
			break;
		case 908:
			env->data_bus[898] = tmp;
			return 1;
			break;
		case 909:
			env->data_bus[899] = tmp;
			return 1;
			break;
		case 910:
			env->data_bus[900] = tmp;
			return 1;
			break;
		case 911:
			env->data_bus[901] = tmp;
			return 1;
			break;
		case 912:
			env->data_bus[902] = tmp;
			return 1;
			break;
		case 913:
			env->data_bus[903] = tmp;
			return 1;
			break;
		case 914:
			env->data_bus[904] = tmp;
			return 1;
			break;
		case 915:
			env->data_bus[905] = tmp;
			return 1;
			break;
		case 916:
			env->data_bus[906] = tmp;
			return 1;
			break;
		case 917:
			env->data_bus[907] = tmp;
			return 1;
			break;
		case 918:
			env->data_bus[908] = tmp;
			return 1;
			break;
		case 919:
			env->data_bus[909] = tmp;
			return 1;
			break;
		case 920:
			env->data_bus[910] = tmp;
			return 1;
			break;
		case 921:
			env->data_bus[911] = tmp;
			return 1;
			break;
		case 922:
			env->data_bus[912] = tmp;
			return 1;
			break;
		case 923:
			env->data_bus[913] = tmp;
			return 1;
			break;
		case 924:
			env->data_bus[914] = tmp;
			return 1;
			break;
		case 925:
			env->data_bus[915] = tmp;
			return 1;
			break;
		case 926:
			env->data_bus[916] = tmp;
			return 1;
			break;
		case 927:
			env->data_bus[917] = tmp;
			return 1;
			break;
		case 928:
			env->data_bus[918] = tmp;
			return 1;
			break;
		case 929:
			env->data_bus[919] = tmp;
			return 1;
			break;
		case 930:
			env->data_bus[920] = tmp;
			return 1;
			break;
		case 931:
			env->data_bus[921] = tmp;
			return 1;
			break;
		case 932:
			env->data_bus[922] = tmp;
			return 1;
			break;
		case 933:
			env->data_bus[923] = tmp;
			return 1;
			break;
		case 934:
			env->data_bus[924] = tmp;
			return 1;
			break;
		case 935:
			env->data_bus[925] = tmp;
			return 1;
			break;
		case 936:
			env->data_bus[926] = tmp;
			return 1;
			break;
		case 937:
			env->data_bus[927] = tmp;
			return 1;
			break;
		case 938:
			env->data_bus[928] = tmp;
			return 1;
			break;
		case 939:
			env->data_bus[929] = tmp;
			return 1;
			break;
		case 940:
			env->data_bus[930] = tmp;
			return 1;
			break;
		case 941:
			env->data_bus[931] = tmp;
			return 1;
			break;
		case 942:
			env->data_bus[932] = tmp;
			return 1;
			break;
		case 943:
			env->data_bus[933] = tmp;
			return 1;
			break;
		case 944:
			env->data_bus[934] = tmp;
			return 1;
			break;
		case 945:
			env->data_bus[935] = tmp;
			return 1;
			break;
		case 946:
			env->data_bus[936] = tmp;
			return 1;
			break;
		case 947:
			env->data_bus[937] = tmp;
			return 1;
			break;
		case 948:
			env->data_bus[938] = tmp;
			return 1;
			break;
		case 949:
			env->data_bus[939] = tmp;
			return 1;
			break;
		case 950:
			env->data_bus[940] = tmp;
			return 1;
			break;
		case 951:
			env->data_bus[941] = tmp;
			return 1;
			break;
		case 952:
			env->data_bus[942] = tmp;
			return 1;
			break;
		case 953:
			env->data_bus[943] = tmp;
			return 1;
			break;
		case 954:
			env->data_bus[944] = tmp;
			return 1;
			break;
		case 955:
			env->data_bus[945] = tmp;
			return 1;
			break;
		case 956:
			env->data_bus[946] = tmp;
			return 1;
			break;
		case 957:
			env->data_bus[947] = tmp;
			return 1;
			break;
		case 958:
			env->data_bus[948] = tmp;
			return 1;
			break;
		case 959:
			env->data_bus[949] = tmp;
			return 1;
			break;
		case 960:
			env->data_bus[950] = tmp;
			return 1;
			break;
		case 961:
			env->data_bus[951] = tmp;
			return 1;
			break;
		case 962:
			env->data_bus[952] = tmp;
			return 1;
			break;
		case 963:
			env->data_bus[953] = tmp;
			return 1;
			break;
		case 964:
			env->data_bus[954] = tmp;
			return 1;
			break;
		case 965:
			env->data_bus[955] = tmp;
			return 1;
			break;
		case 966:
			env->data_bus[956] = tmp;
			return 1;
			break;
		case 967:
			env->data_bus[957] = tmp;
			return 1;
			break;
		case 968:
			env->data_bus[958] = tmp;
			return 1;
			break;
		case 969:
			env->data_bus[959] = tmp;
			return 1;
			break;
		case 970:
			env->data_bus[960] = tmp;
			return 1;
			break;
		case 971:
			env->data_bus[961] = tmp;
			return 1;
			break;
		case 972:
			env->data_bus[962] = tmp;
			return 1;
			break;
		case 973:
			env->data_bus[963] = tmp;
			return 1;
			break;
		case 974:
			env->data_bus[964] = tmp;
			return 1;
			break;
		case 975:
			env->data_bus[965] = tmp;
			return 1;
			break;
		case 976:
			env->data_bus[966] = tmp;
			return 1;
			break;
		case 977:
			env->data_bus[967] = tmp;
			return 1;
			break;
		case 978:
			env->data_bus[968] = tmp;
			return 1;
			break;
		case 979:
			env->data_bus[969] = tmp;
			return 1;
			break;
		case 980:
			env->data_bus[970] = tmp;
			return 1;
			break;
		case 981:
			env->data_bus[971] = tmp;
			return 1;
			break;
		case 982:
			env->data_bus[972] = tmp;
			return 1;
			break;
		case 983:
			env->data_bus[973] = tmp;
			return 1;
			break;
		case 984:
			env->data_bus[974] = tmp;
			return 1;
			break;
		case 985:
			env->data_bus[975] = tmp;
			return 1;
			break;
		case 986:
			env->data_bus[976] = tmp;
			return 1;
			break;
		case 987:
			env->data_bus[977] = tmp;
			return 1;
			break;
		case 988:
			env->data_bus[978] = tmp;
			return 1;
			break;
		case 989:
			env->data_bus[979] = tmp;
			return 1;
			break;
		case 990:
			env->data_bus[980] = tmp;
			return 1;
			break;
		case 991:
			env->data_bus[981] = tmp;
			return 1;
			break;
		case 992:
			env->data_bus[982] = tmp;
			return 1;
			break;
		case 993:
			env->data_bus[983] = tmp;
			return 1;
			break;
		case 994:
			env->data_bus[984] = tmp;
			return 1;
			break;
		case 995:
			env->data_bus[985] = tmp;
			return 1;
			break;
		case 996:
			env->data_bus[986] = tmp;
			return 1;
			break;
		case 997:
			env->data_bus[987] = tmp;
			return 1;
			break;
		case 998:
			env->data_bus[988] = tmp;
			return 1;
			break;
		case 999:
			env->data_bus[989] = tmp;
			return 1;
			break;
		case 1000:
			env->data_bus[990] = tmp;
			return 1;
			break;
		case 1001:
			env->data_bus[991] = tmp;
			return 1;
			break;
		case 1002:
			env->data_bus[992] = tmp;
			return 1;
			break;
		case 1003:
			env->data_bus[993] = tmp;
			return 1;
			break;
		case 1004:
			env->data_bus[994] = tmp;
			return 1;
			break;
		case 1005:
			env->data_bus[995] = tmp;
			return 1;
			break;
		case 1006:
			env->data_bus[996] = tmp;
			return 1;
			break;
		case 1007:
			env->data_bus[997] = tmp;
			return 1;
			break;
		case 1008:
			env->data_bus[998] = tmp;
			return 1;
			break;
		case 1009:
			env->data_bus[999] = tmp;
			return 1;
			break;
		case 1010:
			env->data_bus[1000] = tmp;
			return 1;
			break;
		case 1011:
			env->data_bus[1001] = tmp;
			return 1;
			break;
		case 1012:
			env->data_bus[1002] = tmp;
			return 1;
			break;
		case 1013:
			env->data_bus[1003] = tmp;
			return 1;
			break;
		case 1014:
			env->data_bus[1004] = tmp;
			return 1;
			break;
		case 1015:
			env->data_bus[1005] = tmp;
			return 1;
			break;
		case 1016:
			env->data_bus[1006] = tmp;
			return 1;
			break;
		case 1017:
			env->data_bus[1007] = tmp;
			return 1;
			break;
		case 1018:
			env->data_bus[1008] = tmp;
			return 1;
			break;
		case 1019:
			env->data_bus[1009] = tmp;
			return 1;
			break;
		case 1020:
			env->data_bus[1010] = tmp;
			return 1;
			break;
		case 1021:
			env->data_bus[1011] = tmp;
			return 1;
			break;
		case 1022:
			env->data_bus[1012] = tmp;
			return 1;
			break;
		case 1023:
			env->data_bus[1013] = tmp;
			return 1;
			break;
		case 1024:
			env->data_bus[1014] = tmp;
			return 1;
			break;
		case 1025:
			env->data_bus[1015] = tmp;
			return 1;
			break;
		case 1026:
			env->data_bus[1016] = tmp;
			return 1;
			break;
		case 1027:
			env->data_bus[1017] = tmp;
			return 1;
			break;
		case 1028:
			env->data_bus[1018] = tmp;
			return 1;
			break;
		case 1029:
			env->data_bus[1019] = tmp;
			return 1;
			break;
		case 1030:
			env->data_bus[1020] = tmp;
			return 1;
			break;
		case 1031:
			env->data_bus[1021] = tmp;
			return 1;
			break;
		case 1032:
			env->data_bus[1022] = tmp;
			return 1;
			break;
		case 1033:
			env->data_bus[1023] = tmp;
			return 1;
			break;
		case 1034:
			env->CoinBase = tmp;
			return 8;
			break;
		case 1035:
			env->TimeStamp = tmp;
			return 8;
			break;
		case 1036:
			env->Number = tmp;
			return 8;
			break;
		case 1037:
			env->Difficulty = tmp;
			return 8;
			break;
		case 1038:
			env->GasLimit = tmp;
			return 8;
			break;
		default:
			return 8;
	}
}

int ppdl_cpu_gdb_read_fifo(CPUState *cs, uint8_t *mem_buf, int fifo) {
	PPDLCPU *cpu = PPDL_CPU(cs);
	CPUPPDLState *env = &cpu->env;
	int cur_data_size = 0;
	switch (fifo) {
	}
	/*
	 * convert to bits
	 */
	return 8*cur_data_size;
}

int ppdl_cpu_gdb_write_fifo(CPUState *cs, uint8_t *mem_buf, int fifo, int data_size) {
	PPDLCPU *cpu = PPDL_CPU(cs);
	CPUPPDLState *env = &cpu->env;
	data_size /= 8;
	switch (fifo) {
	}
	return 0;
}

int ppdl_cpu_gdb_info_fifo(CPUState *cs, char *buf, int arg) {
	const char* GDB_FIFO_STRUCT = "34;vr0,8,32;vr1,8,32;vr2,8,32;vr3,8,32;vr4,8,32;vr5,8,32;vr6,8,32;vr7,8,32;vr8,8,32;vr9,8,32;vr10,8,32;vr11,8,32;vr12,8,32;vr13,8,32;vr14,8,32;vr15,8,32;vr16,8,32;vr17,8,32;vr18,8,32;vr19,8,32;vr20,8,32;vr21,8,32;vr22,8,32;vr23,8,32;vr24,8,32;vr25,8,32;vr26,8,32;vr27,8,32;vr28,8,32;vr29,8,32;vr30,8,32;vr31,8,32;afifo,8,32;wfifo,8,32;";
	strcpy(buf, GDB_FIFO_STRUCT);
	return strlen(GDB_FIFO_STRUCT);
}
