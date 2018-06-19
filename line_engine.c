#include "minishell.h"

/*
t_key	t[NB_KEY] = {
	{ARROW_LEFT, line->move_left},
	{ARROW_RIGHT, line->move_right},
	{ARROW_UP, line->history_up},
	{ARROW_DOWN, line->history_down},
	{MY_DELECT, line->delete_key},
	{MY_END, line->move_nright},
	{MY_HOME, line->move_nleft},
	{CONTRL_L, line->mv_left_word},
	{CONTRL_H, line->mv_right_word},
	{CONTRL_A, line->cp_all},
	{CONTRL_B, line->cp_begin},
	{CONTRL_E, line->cp_end},
	{CONTRL_AT, line->cut_all},
	{CONTRL_HASH, line->cut_begin},
	{CONTRL_PERCENT, line->cut_end},
	{CONTRL_P, line->paste},
	{CONTRL_F, line->go_up},
	{CONTRL_N, line->go_down},
}
*/

static void	init_for_enginie_2(t_key *t, t_line *line)
{
	t[12].a_key = CONTRL_S;
	t[12].func = line->cut_all;
	t[13].a_key = CONTRL_HASH;
	t[13].func = line->cut_begin;
	t[14].a_key = CONTRL_PERCENT;
	t[14].func = line->cut_end;
	t[15].a_key = CONTRL_P;
	t[15].func = line->paste;
	t[16].a_key = CONTRL_F;
	t[16].func = line->go_up;
	t[17].a_key = CONTRL_N;
	t[17].func = line->go_down;
	t[18].a_key = EOF;
	t[18].func = line->cut_all;
}

static void	init_for_engine(t_key *t, t_line *line)
{
	t[0].a_key = ARROW_LEFT;
	t[0].func = line->move_left;
	t[1].a_key = ARROW_RIGHT;
	t[1].func = line->move_right;
	t[2].a_key = ARROW_UP;
	t[2].func = line->history_up;
	t[3].a_key = ARROW_DOWN;
	t[3].func = line->history_down;
	t[4].a_key = MY_DELECT;
	t[4].func = line->delete_key;
	t[5].a_key = MY_END;
	t[5].func = line->move_nright;
	t[6].a_key = MY_HOME;
	t[6].func = line->move_nleft;
	t[7].a_key = CONTRL_L;
	t[7].func = line->mv_left_word;
	t[8].a_key = CONTRL_H;
	t[8].func = line->mv_right_word;
	t[9].a_key = CONTRL_A;
	t[9].func = line->cp_all;
	t[10].a_key = CONTRL_B;
	t[10].func = line->cp_begin;
	t[11].a_key = CONTRL_E;
	t[11].func = line->cp_end;
	init_for_enginie_2(t, line);
}

int		engine(t_line *line, unsigned long  key)
{
	int		i;
	t_key	t[NB_KEY];

	i = 0;
	if ((32 <= key && key <= 126))
		line->printable(line, key);
	else
	{
		init_for_engine(t, line);
		while (i < NB_KEY)
		{
			if (key == (t[i].a_key))
				t[i].func(line);
			i++;
		}
	}
	return (0);
}
