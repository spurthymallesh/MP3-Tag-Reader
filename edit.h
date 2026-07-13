#ifndef EDIT_H
#define EDIT_H

#include "mp3tag.h"

Status edit_tag(TagInfo *tag);
Status edit_title(TagInfo *tag);
// Status edit_artist(TagInfo *tag);
// Status edit_album(TagInfo *tag);
// Status edit_year(TagInfo *tag);
Status edit_frame(TagInfo *tag, char *target_frame);

#endif