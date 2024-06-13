#include "Linker.h"


extern World* Pointer;

void Linker::Link(Vector *Classes) {

    println("");

    for (int i = 0; i < Classes->Count; ++i) {

        Class* Linkable = static_cast<Class *>(Classes->Get(i));

        Linkable->Linked = true;

        Array* LinkablePool = Linkable->Pool;

        printf("Linking class: ");

        Linkable->Name->Log();

        println("");

        for (int j = 1; j < LinkablePool->Length-1; ++j) {

            Object* Element = LinkablePool->GetObject(j);

            switch (Element->Native) {

                case NClass:

                    for (int k = 0; k < Classes->Count; ++k) {

                        Class* Target = static_cast<Class *>(Element);
                        Class* Find = static_cast<Class *>(Classes->Get(k));
/*
                        printf("Linking class: ");
                        Target->Name->Log();
                        printf(" with a: ");
                        Find->Name->Log();
                        printf("\n");
*/

                        if (Find->Name->Equals(Target->Name)) {

                            if (Linkable->Super == Target) {
                                Linkable->Super = Find;
                            }

                            LinkablePool->Set(j,Find);
                            break;
                        }

                    }

                    break;
                case NMethod:

                    for (int k = 0; k < Classes->Count; ++k) {

                        bool Linked = false;

                        Class* Find = static_cast<Class *>(Classes->Get(k));

                        for (int l = 0; l < Find->Methods->Length; ++l) {

                            Method* Target = static_cast<Method *>(Element);
                            Method* MethodFind = static_cast<Method *>(Find->Methods->GetObject(l));
/*
                            printf("Linking method: ");
                            Target->Owner->Name->Log();
                            printf("::");
                            Target->Name->Log();
                            printf(" with a: ");
                            MethodFind->Owner->Name->Log();
                            printf("::");
                            MethodFind->Name->Log();
                            printf("\n");
*/
                            if (!Target->Owner->Name->Equals(MethodFind->Owner->Name)) {
                                break;
                            }

                            if (Target->Name->Equals(MethodFind->Name) && Target->Signature->Equals(MethodFind->Signature)) {
                                LinkablePool->Set(j,MethodFind);
                                Linked = true;
                            }

                            if (Linked) {
                                break;
                            }

                        }

                        if (Linked) {
                            break;
                        }

                    }

                    break;
                case NField:

                    for (int k = 0; k < Classes->Count; ++k) {

                        bool Linked = false;

                        Class* Find = static_cast<Class *>(Classes->Get(k));

                        for (int l = 0; l < Find->Fields->Length; ++l) {

                            Field* Target = static_cast<Field *>(Element);
                            Field* MethodFind = static_cast<Field *>(Find->Fields->GetObject(l));
/*
                            printf("Linking field: ");
                            Target->Owner->Name->Log();
                            printf("::");
                            Target->Name->Log();
                            printf(" with a: ");
                            MethodFind->Owner->Name->Log();
                            printf("::");
                            MethodFind->Name->Log();
                            printf("\n");
*/
                            if (!Target->Owner->Name->Equals(MethodFind->Owner->Name)) {
                                break;
                            }

                            if (Target->Name->Equals(MethodFind->Name) && Target->Signature->Equals(MethodFind->Signature)) {
                                LinkablePool->Set(j,MethodFind);
                                Linked = true;
                            }

                            if (Linked) {
                                break;
                            }

                        }

                        if (Linked) {
                            break;
                        }

                    }

                    break;
            }

        }

    }

}
