/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <arrow-glib/data-type.hpp>
#include <arrow-glib/enums.h>
#include <arrow-glib/error.hpp>
#include <arrow-glib/field.hpp>
#include <arrow-glib/type.hpp>

G_BEGIN_DECLS

/**
 * SECTION: composite-data-type
 * @section_id: composite-data-type-classes
 * @title: Composite data type classes
 * @include: arrow-glib/arrow-glib.h
 *
 * #GArrowListDataType is a class for list data type.
 *
 * #GArrowStructDataType is a class for struct data type.
 */

G_DEFINE_TYPE(GArrowListDataType,                \
              garrow_list_data_type,             \
              GARROW_TYPE_DATA_TYPE)

static void
garrow_list_data_type_init(GArrowListDataType *object)
{
}

static void
garrow_list_data_type_class_init(GArrowListDataTypeClass *klass)
{
}

/**
 * garrow_list_data_type_new:
 * @field: The field of elements
 *
 * Returns: The newly created list data type.
 */
GArrowListDataType *
garrow_list_data_type_new(GArrowField *field)
{
  auto arrow_field = garrow_field_get_raw(field);
  auto arrow_data_type =
    std::make_shared<arrow::ListType>(arrow_field);

  GArrowListDataType *data_type =
    GARROW_LIST_DATA_TYPE(g_object_new(GARROW_TYPE_LIST_DATA_TYPE,
                                       "data-type", &arrow_data_type,
                                       NULL));
  return data_type;
}

/**
 * garrow_list_data_type_get_value_field:
 * @list_data_type: A #GArrowListDataType.
 *
 * Returns: (transfer full): The field of value.
 */
GArrowField *
garrow_list_data_type_get_value_field(GArrowListDataType *list_data_type)
{
  auto arrow_data_type =
    garrow_data_type_get_raw(GARROW_DATA_TYPE(list_data_type));
  auto arrow_list_data_type =
    static_cast<arrow::ListType *>(arrow_data_type.get());

  auto arrow_field = arrow_list_data_type->value_field();
  auto field = garrow_field_new_raw(&arrow_field);

  return field;
}


G_DEFINE_TYPE(GArrowStructDataType,                \
              garrow_struct_data_type,             \
              GARROW_TYPE_DATA_TYPE)

static void
garrow_struct_data_type_init(GArrowStructDataType *object)
{
}

static void
garrow_struct_data_type_class_init(GArrowStructDataTypeClass *klass)
{
}

/**
 * garrow_struct_data_type_new:
 * @fields: (element-type GArrowField): The fields of the struct.
 *
 * Returns: The newly created struct data type.
 */
GArrowStructDataType *
garrow_struct_data_type_new(GList *fields)
{
  std::vector<std::shared_ptr<arrow::Field>> arrow_fields;
  for (GList *node = fields; node; node = g_list_next(node)) {
    auto field = GARROW_FIELD(node->data);
    auto arrow_field = garrow_field_get_raw(field);
    arrow_fields.push_back(arrow_field);
  }

  auto arrow_data_type = std::make_shared<arrow::StructType>(arrow_fields);
  GArrowStructDataType *data_type =
    GARROW_STRUCT_DATA_TYPE(g_object_new(GARROW_TYPE_STRUCT_DATA_TYPE,
                                         "data-type", &arrow_data_type,
                                         NULL));
  return data_type;
}

G_END_DECLS
