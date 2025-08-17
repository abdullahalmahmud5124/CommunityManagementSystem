#include <stdio.h>
#include <string.h>

#define MAXR 20
#define MAXS 10
#define MAXQ 20

enum Role
{
    RES=1,
    STAFF=2
};
struct Resident
{
    int id;
    char name[20];
    int flat;
    enum Role role;
};

int main()
{
    struct Resident r[MAXR]; int rc=0;               // array for residents
    char ann[MAXS][30]; int top=-1;                 // stack for announcements
    int q[MAXQ], qh=0, qt=0, qs=0, tid=100;         // circular queue for tickets
    int ch=0;

    while (1)
    {
        printf("\n--- Community Management ---\n");
        printf(" 1.Add resident \n 2.List residents \n 3.New ticket \n 4.Serve ticket \n 5.Show tickets \n 6.Post announce \n 7.Remove announce \n 8.Show announce \n 9.Exit\n");
        printf("Choose: ");
        if (scanf("%d",&ch)!=1)
        {
            return 0;
        }
        if (ch==1)
        {                                               // add resident
            if (rc>=MAXR)
            {
                printf("Resident list full!\n");
            }
            else
            {
                r[rc].id=rc+1;
                printf("Name(no space): "); scanf("%19s", r[rc].name);
                printf("Flat no: "); scanf("%d", &r[rc].flat);
                printf("Role 1=RES 2=STAFF: "); int rr; scanf("%d",&rr);
                r[rc].role = (rr==2)?STAFF:RES;
                printf("Added ID %d\n", r[rc].id); rc++;
            }
        }
        else if (ch==2)                                    // list residents
        {
            if (rc==0)
            {
                printf("No residents.\n");
            }
            else
            {
                printf("ID  Name               Flat  Role\n");
                for (int i=0;i<rc;i++)
                {
                    printf("%-3d %-18s %-5d %s\n", r[i].id, r[i].name, r[i].flat,
                            (r[i].role==STAFF?"STAFF":"RES"));
                }

            }
        }
        else if (ch==3)
        {                                         // enqueue ticket
            if (qs>=MAXQ)
            {
                printf("Ticket queue full!\n");
            }
            else
            {
                q[qt]=tid++;
                qt=(qt+1)%MAXQ; qs++;
                printf("Ticket created.\n");
            }
        }
        else if (ch==4)
        {                                               // dequeue ticket
            if (qs==0)
            {
                printf("No tickets.\n");
            }
            else
            {
                int t=q[qh];
                qh=(qh+1)%MAXQ; qs--;
                printf("Serving ticket %d\n", t);
            }
        }
        else if (ch==5)
        {                            // show queue
            if (qs==0)
            {
                printf("No tickets.\n");
            }
            else
            {
                printf("Tickets: ");
                for (int i=0,idx=qh;i<qs;i++,idx=(idx+1)%MAXQ)
                {
                    printf("%d ", q[idx]);
                    printf("\n");
                }
            }
        }
        else if (ch==6)
        {                            // push announcement
            if (top>=MAXS-1)
            {
                 printf("Announcement stack full!\n");
            }
            else
            {
                top++;
                printf("Text(no space,<=29): ");
                scanf("%29s", ann[top]);
                printf("Posted.\n");
            }
        }
        else if (ch==7)
        {                            // pop announcement
            if (top<0)
            {
                printf("No announcements.\n");
            }
            else
            {
                printf("Removed: %s\n", ann[top]);
                top--;
            }
        }
        else if (ch==8)
        {                            // show stack
            if (top<0)
            {
                printf("No announcements.\n");
            }
            else
            {
                printf("Announcements (latest first):\n");
                for (int i=top;i>=0;i--)
                {
                    printf("%s\n", ann[i]);
                }
            }
        }
        else if (ch==9)
        {
            printf("Bye!\n");
            break;
        }
        else printf("Invalid choice.\n");
    }
    return 0;
}
