#include <stdio.h>

//#include "add-ndrtosn.h"
#define RES_PL 1

#include "sn.h"

//#include "d1-ndrtosn.h"
//#define RES_PL 22

//#include "d5-ndrtosn.h"
//#define RES_PL 110

#define pres1 "[7:0]"
#define pres2 "[5:0]"

int main()
{
    int i, j;

    //module header
    printf(
    "module sn(\n"
    "    input clk,\n"
    "    input rst,\n"
    "    output reg [5:0] led\n"
    ");\n\n");

    // INH
    printf("`define INH(place) ((place) == 0 ? 255 : 0)\n\n");

    //place and fireability arrays
    printf("reg %s p [0:%d];\n", pres1, m-1);
    printf("reg %s p_next [0:%d];\n", pres1, m-1);
    printf("reg %s f [0:%d];\n", pres1, n-1);

    printf("integer i;\n\n");

    // Combinatorial logic block
    printf("always @(*) begin\n\n");

    // Default next-state assignments
    printf("\tfor(i=0;i<%d;i=i+1)\n", m);
    printf("\t\tp_next[i] = p[i];\n\n");

    // Fireability calculations
    for(j=0;j<n;j++)
    {
        printf("\tf[%d] = 255;\n", j);

        for(i=0;i<m;i++)
        {
            if(b[i][j] != 0)
            {
                if(b[i][j] > 0 && b[i][j] != 1)
                {
                    printf(
		    "\tf[%d] = (f[%d] >= p[%d]/%d) ? p[%d]/%d : f[%d];\n",
                    j,j,i,b[i][j],i,b[i][j],j);
                }
                else if(b[i][j] == 1)
                {
                    printf(
                    "\tf[%d] = (f[%d] > p[%d]) ? p[%d] : f[%d];\n",
                    j,j,i,i,j);
                }
                else if(b[i][j] < 0)
                {
                    printf(
		    "\tf[%d] = (f[%d] >= `INH(p[%d])) ? `INH(p[%d]) : f[%d];\n",
                    j,j,i,i,j);
                }
            }
        }

        printf("\n");
    }

    // Priority arcs
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(r[i][j] > 0)
            {
                printf("\tif(f[%d] > 0)\n", i);
                printf("\t\tf[%d] = 0;\n", j);
            }
        }
    }

    for(j=0;j<n;j++) {
        if(b[j][j] > 1) {
            printf("\tif (%d*f[%d] <= p[%d]) begin\n",b[j][j],j,j);
        }
        else {
            printf("\tif (f[%d] <= p[%d]) begin\n",j,j);
        }
        for(i=0;i<m;i++)
        {
            if(b[i][j] > 0)
            {
                if(b[i][j] != 1)
                {
                    printf("\t\tp_next[%d] = p[%d] - %d*f[%d];\n",i,i,b[i][j],j);
                }
                else
                {
                    printf("\t\tp_next[%d] = p[%d] - f[%d];\n",i,i,j);
                }
            }
        }

        // Produce tokens
        for(i=0;i<m;i++)
        {
            if(d[i][j] > 0)
            {
                if(d[i][j] != 1)
                {
                    printf("\t\tp_next[%d] = p[%d] + %d*f[%d];\n",i,i,d[i][j],j);
                }
                else
                {
                    printf("\t\tp_next[%d] = p[%d] + f[%d];\n",i,i,j);
                }
            }
        }

        printf("\tend\n\n");
    }

    printf("end\n\n");

    // Sequential block
    printf("always @(posedge clk) begin\n\n");

    // set initial values
    printf("\tif(~rst) begin\n");

    for(i=0;i<m;i++)
    {
        printf("\t\tp[%d] <= 8'd%d;\n", i, mu[i]);
    }

    printf("\t\tled <= 6'b111111;\n");

    printf("\tend\n");

    printf("\telse begin\n");
    printf("\t\tfor(i=0;i<%d;i=i+1)\n", m);
    printf("\t\t\tp[i] <= p_next[i];\n\n");
    printf("\t\tled <= ~p_next[%d]%s;\n", RES_PL, pres2);
    printf("\tend\n");
    printf("end\n\n");
    printf("endmodule\n");

    return 0;
}
