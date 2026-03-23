@startuml

' hide the spot
hide circle

' avoid problems with angled crows feet
skinparam linetype ortho

entity "GlobalContext" {
  *e1_id : number <<generated>>
  --
  *name : text
  description : text
}

entity "ServerActor" {
  *e2_id : number <<generated>>
  --
  *e1_id : number <<FK>>
  other_details : text
}

entity "ClientActor" {
  *e3_id : number <<generated>>
  --
  e1_id : number <<FK>>
  other_details : text
}

GlobalContext ||--|| ServerActor
GlobalContext ||--o{ ClientActor

@enduml
