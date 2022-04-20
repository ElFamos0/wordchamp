import { createWebHashHistory, createRouter } from "vue-router";
import Home from "@/views/Home.vue";
import Random from "@/views/Random.vue";
import Word from "@/views/Word.vue";
import Register from "@/views/Register.vue";
import Login from "@/views/Login.vue";
import Logout from "@/views/Logout.vue";
import Profile from "@/views/Profile.vue";

import ProfileMain from "@/components/ProfileMain.vue";
import axiosAuth from '@/api/axios-auth'

const routes = [
  {
    path: "/",
    name: "Home",
    component: Home,
    meta: {
      title: 'Wordchamp - Maison',
      metaTags: [
        {
          name: 'description',
          content: 'Ceci est une description.'
        },
        {
          property: 'og:description',
          content: 'Ceci est une description.'
        }
      ]
    }
  },
  {
    path: "/random",
    name: "About",
    component: Random,
    meta: {
      title: 'Wordchamp - Aléatoire',
    }
  },
  {
    path: "/word",
    name: "Word",
    component: Word,
		meta: { 
      requiresAuth: true,
      title: 'Wordchamp - Le Jeu',
    }
  },
  {
    path: "/register",
    name: "Register",
    component: Register,
    meta: {
      title: 'Wordchamp - Enregistrement',
    }
  },
  {
    path: "/login",
    name: "Login",
    component: Login,
    meta: {
      title: 'Wordchamp - Connection',
    }
  },
  {
    path: "/logout",
    name: "Logout",
    component: Logout,
    meta: {
      title: 'Wordchamp - Déconnection',
    }
  },
  {
    path: "/profile",
    name: "Profile",
    component: Profile,
    children: [
      {
        path: '',
        component: ProfileMain,
      },
      {
        path: 'historique',
        component: ProfileMain,
      },
    ],
    meta: {
      requiresAuth: true,
      title: 'Wordchamp - Le Profil',
    }
  },
];

const router = createRouter({
  history: createWebHashHistory(),
  routes,
});


router.beforeEach((to, from, next) => {
	let token = localStorage.getItem('token');
	let requireAuth = to.matched.some(record => record.meta.requiresAuth);

	if (!requireAuth) {
		next();
	}

	if (requireAuth && !token) {
		next('/login');
	}

	if (to.path === '/login') {
		if (token) {
			axiosAuth.post('/verify-token').then(() => {
				next('/word');
			}).catch(() => {
				next();
			});
		}
		else {
			next();
		}
	}

	if (requireAuth && token) {
		axiosAuth.post('/verify-token').then(() => {
			next();
		}).catch(() => {
			next('/login');
		})
	}
});

router.beforeEach((to, from, next) => {
  // This goes through the matched routes from last to first, finding the closest route with a title.
  // e.g., if we have `/some/deep/nested/route` and `/some`, `/deep`, and `/nested` have titles,
  // `/nested`'s will be chosen.
  const nearestWithTitle = to.matched.slice().reverse().find(r => r.meta && r.meta.title);

  // Find the nearest route element with meta tags.
  const nearestWithMeta = to.matched.slice().reverse().find(r => r.meta && r.meta.metaTags);

  const previousNearestWithMeta = from.matched.slice().reverse().find(r => r.meta && r.meta.metaTags);

  // If a route with a title was found, set the document (page) title to that value.
  if(nearestWithTitle) {
    document.title = nearestWithTitle.meta.title;
  } else if(previousNearestWithMeta) {
    document.title = previousNearestWithMeta.meta.title;
  }

  // Remove any stale meta tags from the document using the key attribute we set below.
  Array.from(document.querySelectorAll('[data-vue-router-controlled]')).map(el => el.parentNode.removeChild(el));

  // Skip rendering meta tags if there are none.
  if(!nearestWithMeta) return next();

  // Turn the meta tag definitions into actual elements in the head.
  nearestWithMeta.meta.metaTags.map(tagDef => {
    const tag = document.createElement('meta');

    Object.keys(tagDef).forEach(key => {
      tag.setAttribute(key, tagDef[key]);
    });

    // We use this to track which meta tags we create so we don't interfere with other ones.
    tag.setAttribute('data-vue-router-controlled', '');

    return tag;
  })
  // Add the meta tags to the document head.
  .forEach(tag => document.head.appendChild(tag));

  next();
});

export default router;
