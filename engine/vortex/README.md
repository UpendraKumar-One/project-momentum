# Vortex Engine Namespace Guide

This document outlines the strict namespace architecture used throughout the Vortex Engine to ensure clean separation of concerns and AAA decoupling.

`namespace Vortex {}` # The root namespace for the entire engine. Contains all major engine subsystems and modules.

## Engine Sub-Namespaces

- `namespace Vortex::Components {}` # Contains all standard ECS data components (e.g., Transform, RigidBody, HitBox, Sprite).
- `namespace Vortex::Ecs {}` # Contains the Data-Oriented Entity Component System framework (e.g., Registry, Entity).
- `namespace Vortex::Renderer {}` # Contains the hardware abstraction layer for graphics and drawing (e.g., RendererAPI, Color, Texture2D).
- `namespace Vortex::Systems {}` # Contains the core logic systems that operate on components (e.g., PhysicsSystem, RenderSystem).

## Core Sub-Namespaces

- `namespace Vortex::Core {}` # Contains foundational systems and wrappers required for the engine to boot and run.
- `namespace Vortex::Core::Containers {}` # Contains custom, highly-optimized data structures and collections (e.g., HashMap, Array).
- `namespace Vortex::Core::InputBackend {}` # Contains the hardware abstraction layer for input processing (Hardware key mapping).
- `namespace Vortex::Core::Math {}` # Contains mathematical primitives and geometry operations (e.g., Vector2, Rectangle).
- `namespace Vortex::Core::Utilities {}` # Contains generic helper functions, algorithms, and engine utilities.


# Naming Conventions followed throughout the project

`Classes & Structs` : PascalCase	
`Functions & Methods`	: camelCase	
`Local Variables`	: snake_case  {For struct members too}
`Member Variables` : m_camelCase
`Constants & Macros` : UPPER_SNAKE_CASE
`Enums` : PascalCase {Enum name as well as Values}
`Namespaces` : snake_case