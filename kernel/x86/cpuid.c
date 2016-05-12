/*
Copyright (C) <2016>  William Taylor Jones <freemicronix@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

regs_t cpu_cpuid(int code)
{
    regs_t r;
    asm volatile("cpuid":"=a"(r.eax),"=b"(r.ebx),
                 "=c"(r.ecx),"=d"(r.edx):"0"(code));
    return r;
}


uint32_t cpu_vendor_name(char *name)
{
        regs_t r = cpu_cpuid(0x00);
        
        char line1[5];
        line1[0] = ((char *) &r.ebx)[0];
        line1[1] = ((char *) &r.ebx)[1];
        line1[2] = ((char *) &r.ebx)[2];
        line1[3] = ((char *) &r.ebx)[3];
        line1[4] = '\0';

        char line2[5];
        line2[0] = ((char *) &r.ecx)[0];
        line2[1] = ((char *) &r.ecx)[1];
        line2[2] = ((char *) &r.ecx)[2];
        line2[3] = ((char *) &r.ecx)[3];
        line2[4] = '\0';
        
        char line3[5];
        line3[0] = ((char *) &r.edx)[0];
        line3[1] = ((char *) &r.edx)[1];
        line3[2] = ((char *) &r.edx)[2];
        line3[3] = ((char *) &r.edx)[3];
        line3[4] = '\0';
                            
        strcpy(name, line1);
        strcat(name, line3);
        strcat(name, line2);
        return 15;
}

char* detect_cpu()
{ 
    static char cpu_name[512] = "x86-noname";
    cpu_vendor_name(cpu_name);
    return cpu_name;
}