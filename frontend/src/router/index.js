import { createWebHistory, createRouter } from "vue-router";
import Home from "@/views/Home.vue";
import Random from "@/views/Random.vue";
import Word from "@/views/Word.vue";

const routes = [
  {
    path: "/",
    name: "Home",
    component: Home,
  },
  {
    path: "/random",
    name: "About",
    component: Random,
  },
  {
    path: "/word",
    name: "Word",
    component: Word,
  },
];

const router = createRouter({
  mode: "hash",
  history: createWebHistory(),
  routes,
});

export default router;
