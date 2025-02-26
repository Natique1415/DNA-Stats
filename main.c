#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

void draw_dna(string seq);
void space(int no_of_space);
void center_text(string text);

int valid_dna(string seq);
int hydrogen_bonds(string seq);
int nucleotide_count(string seq);
int console_width();

int main()
{

    space(2);
    string sequence;
    while (1)
    {
        sequence = get_string("Enter the DNA sequence of the 5' to 3' strand : ");

        if (valid_dna(sequence) == 0)
            break;
    }

    space(2);

    center_text("Options");
    center_text("[1] Draw DNA");
    center_text("[2] Number of Phosphodiester Bond(s) Present");
    center_text("[3] Number of Glycosidic Bond(s) Present");
    center_text("[4] Number of Ribose Sugar(s) Present");
    center_text("[5] Number of Hydrogen Bond(s) Present");
    center_text("[6] Quit");

    space(2);

    while (1)
    {
        int choice = get_int("Enter Selection : ");

        if (choice == 1)
        {
            space(1);
            draw_dna(sequence);
            space(2);
        }

        else if (choice == 2)
        {
            space(1);
            printf("Number of Phosphodiester Bond(s) Present = %i\n", ((2 * nucleotide_count(sequence)) - 2));
            space(2);
        }

        else if (choice == 3)
        {
            space(1);
            printf("Number of Glycosidic Bond(s) Present = %i\n", (2 * nucleotide_count(sequence)));
            space(2);
        }

        else if (choice == 4)
        {
            space(1);
            printf("Number of Ribose Sugar(s) Present = %i\n", (2 * nucleotide_count(sequence)));
            space(2);
        }

        else if (choice == 5)
        {
            space(1);
            printf("Number of Hydrogen Bond(s) Present = %i\n", hydrogen_bonds(sequence));
            space(2);
        }

        else if (choice == 6)
        {
            space(1);
            printf("Twist of fate? Nah, it’s just my DNA.");
            space(2);
            break;
        }
    }
}

int console_width()
{
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
        return 80;
    return w.ws_col;
}

void center_text(string text)
{
    int padding = (console_width() - strlen(text)) / 2;
    if (padding < 0)
        padding = 0;
    printf("%*s%s\n", padding, "", text);
}

void draw_dna(string seq)
{
    printf("5'  3'\n");
    for (int j = 0, m = strlen(seq); j < m; j++)
    {
        if (toupper(seq[j]) == 'A')
        {
            printf("A = T\n");
        }

        if (toupper(seq[j]) == 'T')
        {
            printf("T = A\n");
        }

        if (toupper(seq[j]) == 'C')
        {
            printf("C ≡ G\n");
        }

        if (toupper(seq[j]) == 'G')
        {
            printf("G ≡ C\n");
        }
    }
    printf("3'  5'\n");
}

void space(int no_of_space)
{
    for (int i = 0; i < no_of_space; i++)
    {
        printf("\n");
    }
}

int valid_dna(string seq)
{
    if (strlen(seq) == 0)
        return 1;
    for (int i = 0, n = strlen(seq); i < n; i++)
    {
        if (toupper(seq[i]) != 'A' && toupper(seq[i]) != 'T' && toupper(seq[i]) != 'G' && toupper(seq[i]) != 'C')
        {
            return 1;
        }
    }
    return 0;
}
int nucleotide_count(string seq)
{

    return (int) strlen(seq);
}

int hydrogen_bonds(string seq)
{
    int hydrogen_bonds = 0;

    for (int i = 0, n = strlen(seq); i < n; i++)
    {
        if ('A' == toupper(seq[i]) || 'T' == toupper(seq[i]))
        {
            hydrogen_bonds += 2;
        }

        if ('C' == toupper(seq[i]) || 'G' == toupper(seq[i]))
        {
            hydrogen_bonds += 3;
        }
    }

    return hydrogen_bonds;
}
