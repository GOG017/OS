#include <stdio.h>
#include <string.h>
#include "filesys.h"

void halt()
{
	int i, j;

	/*1. write back the current dir */
	chdir("..");
	iput(cur_path_inode);

	/*2. free the u_ofile and sys_ofile and inode*/
	for (i = 0; i < USERNUM; i++)
	{
		if (user[i].u_uid != 0)
		{
			for (j = 0; j < NOFILE; j++)
			{
				if (user[i].u_ofile[j] != SYSOPENFILE + 1)
				{
					close(i, j);
					user[i].u_ofile[j] = SYSOPENFILE + 1;
				} 	//if
			}	 	//for
		}		  	//if
	}			  	//for

	/*3. write back the filesys to the disk*/
	memcpy(disk + BLOCKSIZ, &filsys, sizeof(struct filsys));
	
	/*4. write data to file*/
	FILE *out = fopen("data", "w");
	fprintf(out, "================= U ================\n");
    for (i = 0; i < PWDNUM; i++)
        if (pwd[i].p_gid == 0)
            break;
	fprintf(out, "%d\n", i);
	for (j = 0; j < i; j++)
		fprintf(out, "%hd %hd %s\n", pwd[j].p_uid, pwd[j].p_gid, pwd[j].password);
	fclose(out);

	/*5. close the file system column*/

	/*6. say GOOD BYE to all the user*/
	printf("\nGood Bye. See You Next Time. Please turn off the switch\n");
	exit(0);
}