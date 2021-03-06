/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <dabeloos@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 15:44:53 by dabeloos          #+#    #+#             */
/*   Updated: 2019/03/12 13:32:38 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "ft_printf.h"
# include "yreader.h"
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# define PLATEAU "Plateau "
# define PIECE "Piece "

/*
** x : coordinate on horizontal axis
** y : coordinate on vertical axis
*/
typedef struct			s_coord
{
	int					x;
	int					y;
}						t_crd;

/*
** s : start
** d : distance
*/
typedef struct			s_range
{
	t_crd				s;
	int					d;
}						t_rng;

/*
** hp : horizontal position
** vp : vertical position
*/
typedef struct			s_map_iterator
{
	t_crd				hp;
	t_crd				vp;
}						t_m_it;

/*
** it : iterator
** p : position on piece
** m_o : origin on map
** m_p : position on map
*/
typedef struct			s_pc_navigation
{
	t_m_it				it;
	t_crd				p;
	t_crd				m_o;
	t_crd				m_p;
}						t_pc_nav;

/*
** v : vertical
** h : horizontal
** b : backslash
** s : slash
** o : owner
*/
typedef struct			s_are
{
	t_rng				*v;
	t_rng				*h;
	t_rng				*b;
	t_rng				*s;
	char				o;
}						t_are;

/*
** w : width
** h : height
** m : map
** a : anchor
*/
typedef struct			s_map
{
	int					w;
	int					h;
	t_are				**m;
	t_crd				a;
}						t_map;

/*
** yrng_o : function to navigate outside the boundary of a range
** yrng_i : function to navigate to the boundary inside a range
*/
typedef struct			s_direction
{
	unsigned char		(*yrng_o)(t_map*, t_crd, t_crd*);
	void				(*yrng_i)(t_map*, t_crd, t_crd*);
}						t_dir;

/*
** s : string
** p : position
*/
typedef struct			s_input
{
	char				*s;
	size_t				p;
}						t_in;

/*
** o : owner
** it : iterator
*/
typedef struct			s_player
{
	char				o;
	t_m_it				it;
}						t_ply;

/*
** map : piece's map
** mic : minimum coordinate
** mac : maximum coordinate
** it : iterator
*/
typedef struct			s_piece
{
	t_map				map;
	t_crd				mic;
	t_crd				mac;
	t_m_it				it;
}						t_pc;

/*
** map : map
** pc : piece
** me : the player who must play now
** en : the other player
*/
typedef struct			s_game_master
{
	t_map				map;
	t_pc				pc;
	t_ply				me;
	t_ply				en;
}						t_gm;

/*
** o : origin
** t : target
** dist : distance
*/
typedef struct			s_yseek_eater
{
	t_crd				o;
	char				t;
	int					dist;
}						t_yseek_eater;

/*
** on_map : coordinate with the board as referential
** on_pc : coordinate with the piece as referential
** score : score (best)
** cur_score : current score
** on_sight : true if at least one piece had a true cur_on_sight
** cur_on_sight : true if the enemy can be seen directly from the current piece
** not_eaten : true if at least one piece can be placed without being "eaten"
** cur_not_eaten : true if the current piece can be placed without being "eaten"
*/
typedef struct			s_yplay
{
	t_crd				on_map;
	t_crd				on_pc;
	int					score;
	int					cur_score;
	unsigned char		on_sight;
	unsigned char		cur_on_sight;
	unsigned char		not_eaten;
	unsigned char		cur_not_eaten;
}						t_yplay;

/*
** ---- parsing ----
** utils.c
*/
char					yc_to_upper(char c);
unsigned int			yatoui_limited(t_in *in);
unsigned char			yvalid_for_map(char c);
unsigned char			yvalid_for_piece(char c);

/*
** freer.c
*/
void					ydereference_rng(t_map *map, int x, int y, t_rng *rng);
void					yfree_ares(t_map *map, int x, int y);
void					yfree_map(t_map *map);
void					yfree_turn(t_map *map, t_pc *pc);
void					yreset_in(t_in *in);

/*
** are_support.c
*/
void					yappend_range(t_rng **dst, t_rng *src);
unsigned char			ymalloc_range(t_rng **rng, int x, int y);

/*
** are_creator.c
*/
unsigned char			yadd_are(char o, int x, int y, t_map *map);

/*
** map_decoder.c
*/
unsigned char			ydecode_map(t_in *in, t_map *map);

/*
** map_creator.c
*/
unsigned char			ymalloc_map(t_map *map);

/*
** piece_decoder.c
*/
unsigned char			ydecode_pc(t_in *in, t_pc *pc, char o);

/*
** piece_cropper.c
*/
unsigned char			ydecode_crop(t_in *in, t_pc *pc);

/*
** dimensions_decoder.c
*/
unsigned char			ydecode_size(t_in *in, int *w, int *h, char *ref);
ssize_t					ymap_read_size(t_map *map);

/*
** turn_decoder.c
*/
unsigned char			yread_turn(t_in *in, t_gm *gm);

/*
** player_decoder.c
*/
unsigned char			ydecode_player(t_in in, t_ply *me, t_ply *en);

/*
** ---- main ----
** utils.c
*/
unsigned char			yis_coord(t_crd crd, t_map *map);
unsigned char			ycoord_equals(t_crd c1, t_crd c2);

/*
** rng_v.c
*/
unsigned char			yrng_v_ho(t_map *map, t_crd in, t_crd *out);
unsigned char			yrng_v_lo(t_map *map, t_crd in, t_crd *out);
void					yrng_v_hi(t_map *map, t_crd in, t_crd *out);

/*
** rng_h.c
*/
unsigned char			yrng_h_ho(t_map *map, t_crd in, t_crd *out);
unsigned char			yrng_h_lo(t_map *map, t_crd in, t_crd *out);
void					yrng_h_hi(t_map *map, t_crd in, t_crd *out);
void					yrng_h_li(t_map *map, t_crd in, t_crd *out);

/*
** rng_b.c
*/
unsigned char			yrng_b_ho(t_map *map, t_crd in, t_crd *out);
unsigned char			yrng_b_lo(t_map *map, t_crd in, t_crd *out);

/*
** rng_s.c
*/
unsigned char			yrng_s_ho(t_map *map, t_crd in, t_crd *out);
unsigned char			yrng_s_lo(t_map *map, t_crd in, t_crd *out);

/*
** position_finder.c
*/
unsigned char			yfind_start_positions(t_gm *gm);

/*
** position_iterator.c
*/
unsigned char			ynext_map_pos(t_ply *ply, t_map *map, t_m_it *it,
							t_crd *anchor);
unsigned char			ynext_pc_pos(t_ply *ply, t_pc *pc, t_m_it *it,
							t_crd *anchor);
void					yreset_pc_pos(t_pc *pc, t_m_it *it);

/*
** pc_place_cond_support.c
*/
unsigned char			yenclosed_piece(t_crd origin, t_pc *pc, t_map *map);
unsigned char			ytest_range(t_crd n, t_crd origin, t_pc *pc,
							t_map *map);
unsigned char			ytest_anchor_range(t_crd n, t_crd origin, t_pc *pc,
							t_map *map);
unsigned char			ycut_ranges(t_crd n, t_crd origin, t_pc *pc,
							t_map *map);

/*
** pc_place_condition.c
*/
unsigned char			ycan_put_piece(t_pc *pc, t_map *map);

/*
** sonar_support.c
*/
void					yidentify_quarter(t_crd o, t_crd d, t_crd *s, t_crd *e);
unsigned char			yfit_backslash(t_gm *gm, t_crd *s, t_crd *e);
unsigned char			yfit_slash(t_gm *gm, t_crd *s, t_crd *e);

/*
** sonar.c
*/
t_crd					ysonar(t_gm *gm, t_crd o, char t, int size);

/*
** distance_scorer.c
*/
int						ydistance(t_crd c1, t_crd c2);
int						yscore_closest(t_gm *gm);

/*
** enemy_on_sight.c
*/
unsigned char			yenemy_on_sight(t_gm *gm);

/*
** enemy_eater.c
*/
unsigned char			yeaten(t_gm *gm);

/*
** player.c
*/
unsigned char			yplay(t_gm *gm);

#endif
