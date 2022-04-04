<template>
  <div class="home">
    <img alt="Vue logo" src="../assets/logo.png">
    <SousTemplate msg="Ceci marche comme une variable de template"/>
  </div>
</template>

<script>
// @ is an alias to /src
import SousTemplate from '@/components/SousTemplate.vue';

export default {
  name: 'home-page',
  components: {
    SousTemplate,
  },
};
</script>
