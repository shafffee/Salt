# Core
  ## Application 
  ## Clock
  ## Core
  ## EntryPoint

# Graphics
  ## Renderer

  ## Batch
  ## Quad
  ## Rect

  ## MonospaceFont
  ## MonospaceText

  ## Vertex
  ## Shader
  ## VertexArray
  ## VertexBuffer
  ## IndexBuffer
  ## TextureManager

# Input
  ## Keyboard
  ## Mouse

# Logging

---

REFACTOR:

# Entry Point
Creates the instance of application and runs it.
EntryPoint -> Application
# App Lifecycle:
defaultOnInit -> OnInit -> defaultRun [OnUpdate] -> OnExit -> defaultOnExit

Application:
  Window*
  Renderer*
  Input*

# Window

----------
# ECS

Entity:
