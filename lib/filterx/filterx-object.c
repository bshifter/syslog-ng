#include "filterx-object.h"

void
filterx_type_init(FilterXType *type)
{
  FilterXType *parent = type->super_type;

  for (gint i = 0; i < G_N_ELEMENTS(type->__methods); i++)
    {
      if (!type->__methods[i])
        type->__methods[i] = parent->__methods[i];
    }
}

void
filterx_object_free_method(FilterXObject *self)
{
  /* empty */
}

void
filterx_object_init_instance(FilterXObject *self, FilterXType *type)
{
  self->ref_cnt = 1;
  self->type = type;
}

FilterXObject *
filterx_object_new(FilterXType *type)
{
  FilterXObject *self = g_new0(FilterXObject, 1);
  filterx_object_init_instance(self, type);
  return self;
}

FilterXObject *
filterx_object_ref(FilterXObject *self)
{
  self->ref_cnt++;
  return self;
}

void
filterx_object_unref(FilterXObject *self)
{
  if (!self)
    return;

  g_assert(self->ref_cnt > 0);
  if (--self->ref_cnt == 0)
    {
      self->type->free_fn(self);
      g_free(self);
    }
}

FilterXType FILTERX_TYPE_NAME(object) =
{
  .super_type = NULL,
  .name = "object",
  .free_fn = filterx_object_free_method,
};